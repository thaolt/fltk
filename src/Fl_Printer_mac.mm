/*
 *  fl_native_printer_mac.cxx
 *
 */
#ifdef __APPLE__

#include <FL/Fl_Printer.H>
#include <FL/fl_ask.H>
#ifdef __APPLE_COCOA__
#import <Cocoa/Cocoa.h>
#endif

extern void fl_quartz_restore_line_style_();

Fl_Printer::Fl_Printer(void)
{
  x_offset = 0;
  y_offset = 0;
}

int Fl_Printer::start_job (int pagecount, int *frompage, int *topage)
//printing using a Quartz graphics context
//returns 0 iff OK
{
  OSStatus status;
  Fl_X::q_release_context();
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 && defined(__APPLE_COCOA__)
  if( [NSPrintPanel instancesRespondToSelector:@selector(runModalWithPrintInfo:)] &&
     [NSPrintInfo instancesRespondToSelector:@selector(PMPrintSession)] ) {
    NSAutoreleasePool *localPool;
    localPool = [[NSAutoreleasePool alloc] init]; 
    NSPrintInfo *info = [NSPrintInfo sharedPrintInfo];
    NSPageLayout *layout = [NSPageLayout pageLayout];
    NSInteger retval = [layout runModal];
    if(retval == NSOKButton) {
      NSPrintPanel *panel = [NSPrintPanel printPanel];
      retval = (NSInteger)[panel runModalWithPrintInfo:info];//from 10.5 only
    }
    if(retval != NSOKButton) {
      Fl::first_window()->show();
      [localPool release];
      return 1;
    }
    printSession = (PMPrintSession)[info PMPrintSession];
    pageFormat = (PMPageFormat)[info PMPageFormat];
    printSettings = (PMPrintSettings)[info PMPrintSettings];
    UInt32 from32, to32;
    PMGetFirstPage(printSettings, &from32); 
    if (frompage) *frompage = (int)from32;
    PMGetLastPage(printSettings, &to32); 
    if (topage) *topage = (int)to32;
    if(topage && *topage > pagecount) *topage = pagecount;
    status = PMSessionBeginCGDocumentNoDialog(printSession, printSettings, pageFormat);
    [localPool release];
  }
  else {
#endif
    
#if !__LP64__
    Boolean accepted;
    status = PMCreateSession(&printSession);
    if (status != noErr) return 1;
    status = PMCreatePageFormat(&pageFormat);
    status = PMSessionDefaultPageFormat(printSession, pageFormat);
    if (status != noErr) return 1;
    status = PMSessionPageSetupDialog(printSession, pageFormat, &accepted);
    if (status != noErr || !accepted) {
      Fl::first_window()->show();
      return 1;
    }
    status = PMCreatePrintSettings(&printSettings);
    if (status != noErr || printSettings == kPMNoPrintSettings) return 1;
    status = PMSessionDefaultPrintSettings (printSession, printSettings);
    if (status != noErr) return 1;
    PMSetPageRange(printSettings, 1, (UInt32)kPMPrintAllPages);
    status = PMSessionPrintDialog(printSession, printSettings, pageFormat, &accepted);
    if (!accepted) status = kPMCancel;
    if (status != noErr) {
      Fl::first_window()->show();
      return 1;
    }
    UInt32 from32, to32;
    PMGetFirstPage(printSettings, &from32); 
    if (frompage) *frompage = (int)from32;
    PMGetLastPage(printSettings, &to32); 
    if (topage) *topage = (int)to32;
    if(topage && *topage > pagecount) *topage = pagecount;
    CFStringRef mystring[1];
    mystring[0] = kPMGraphicsContextCoreGraphics;
    CFArrayRef array = CFArrayCreate(NULL, (const void **)mystring, 1, &kCFTypeArrayCallBacks);
    status = PMSessionSetDocumentFormatGeneration(printSession, kPMDocumentFormatDefault, array, NULL);
    CFRelease(array);
    status = PMSessionBeginDocumentNoDialog(printSession, printSettings, pageFormat);
#endif //__LP64__
    
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 && defined(__APPLE_COCOA__)
  }
#endif
  if (status != noErr) return 1;
  y_offset = x_offset = 0;
  return 0;
}

void Fl_Printer::margins(int *left, int *top, int *right, int *bottom)
{
  PMPaper paper;
  PMGetPageFormatPaper(pageFormat, &paper);
  PMPaperMargins margins;
  PMPaperGetMargins(paper, &margins);
  if (left) *left = (int)(margins.left / scale_x + 0.5);
  if (top) *top = (int)(margins.top / scale_y + 0.5);
  if (right) *right = (int)(margins.right / scale_x + 0.5);
  if (bottom) *bottom = (int)(margins.bottom / scale_y + 0.5);
}

int Fl_Printer::printable_rect(int *w, int *h)
//returns 0 iff OK
{
  OSStatus status;
  PMRect pmRect;
  int x, y;
  
  status = PMGetAdjustedPageRect(pageFormat, &pmRect);
  if (status != noErr) return 1;
  
  x = (int)pmRect.left;
  y = (int)pmRect.top;
  *w = (int)(pmRect.right - x) / scale_x + 1;
  *h = (int)(pmRect.bottom - y) / scale_y + 1;
  return 0;
}

void Fl_Printer::origin(int x, int y)
{
  x_offset = x;
  y_offset = y;
  CGContextRestoreGState(fl_gc);
  CGContextRestoreGState(fl_gc);
  CGContextSaveGState(fl_gc);
  CGContextScaleCTM(fl_gc, scale_x, scale_y);
  CGContextTranslateCTM(fl_gc, x, y);
  CGContextSaveGState(fl_gc);
}

void Fl_Printer::scale (float s_x, float s_y)
{
  scale_x = s_x;
  scale_y = s_y;
  CGContextRestoreGState(fl_gc);
  CGContextRestoreGState(fl_gc);
  CGContextSaveGState(fl_gc);
  CGContextScaleCTM(fl_gc, scale_x, scale_y);
  x_offset = y_offset = 0;
  CGContextSaveGState(fl_gc);
}

int Fl_Printer::start_page (void)
{	
  OSStatus status = PMSessionBeginPageNoDialog(printSession, pageFormat, NULL);
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
  if ( PMSessionGetCGGraphicsContext != NULL ) {
    status = PMSessionGetCGGraphicsContext(printSession, &fl_gc);
  }
  else {
#endif
#if ! __LP64__
    status = PMSessionGetGraphicsContext(printSession,NULL,(void **)&fl_gc);
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
  }
#endif
  PMRect pmRect;
  float win_scale_x, win_scale_y;

  PMPaper paper;
  PMGetPageFormatPaper(pageFormat, &paper);
  PMPaperMargins margins;
  PMPaperGetMargins(paper, &margins);
  
  status = PMGetAdjustedPageRect(pageFormat, &pmRect);
  double h = pmRect.bottom - pmRect.top;
  x_offset = 0;
  y_offset = 0; 
  scale_x = scale_y = 1;
  win_scale_x = win_scale_y = 1;
  image_list_ = NULL;
  CGContextTranslateCTM(fl_gc, margins.left, margins.bottom + h - 0.5f);
  CGContextScaleCTM(fl_gc, win_scale_x, - win_scale_y);
  fl_quartz_restore_line_style_();
  CGContextSetShouldAntialias(fl_gc, false);
  CGContextSaveGState(fl_gc);
  CGContextSaveGState(fl_gc);
  fl_window = (void *)1; // TODO: something better
  fl_clip_region(0);
  return status != noErr;
}

int Fl_Printer::end_page (void)
{	
  CGContextFlush(fl_gc);
  CGContextRestoreGState(fl_gc);
  CGContextRestoreGState(fl_gc);
  OSStatus status = PMSessionEndPageNoDialog(printSession);
  delete_image_list();
  return status != noErr;
}

void Fl_Printer::end_job (void)
{
  OSStatus status;
  
  status = PMSessionError(printSession);
  if (status != noErr) {
    fl_alert ("PM Session error %d", status);
  }
  PMSessionEndDocumentNoDialog(printSession);
  fl_gc = 0;
  Fl::first_window()->show();
}

#endif // __APPLE__

