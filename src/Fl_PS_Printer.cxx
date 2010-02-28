/*
 *  Fl_PS_Printer.cxx
 *
 */
#include <FL/Fl_Device.H>

#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <stdio.h>
#include <math.h>


const int Fl_PSfile_Device::page_formats[NO_PAGE_FORMATS][2]={

// A* // index(Ai) = i
{2384, 3370}, //A0
{1684, 2384}, //A1
{1191, 1684}, //A2
{842, 1191},  //A3
{595, 842},   //A4
{420, 595},   //A5
{297, 420},   //A6
{210, 297},   //A7
{148, 210},   //A8
{105, 148},   //A9

// B* // index(Bi) = i+10
{2920, 4127}, //B0
{2064, 2920}, //B1
{1460, 2064}, //B2
{1032, 1460}, //B3
{729, 1032},  //B4
{516, 729},   //B5
{316, 516},   //B6
{258, 516},   //B7
{181, 258},   //B8
{127, 181},   //B9
{91,127},     //B10

// others (look at Fl_Printer.H} //
{462, 649},  // c5 envelope
{312, 623},  // d1 envelope
{541, 719},
{595, 935},
{1224, 790},  //Ledger landscape
{612, 1009},  //Legal
{612, 790}, //Letter
{791, 1224},  //Ledger
{297, 683}   //Comm10 envelope

};


//  Prolog string 

static const char * prolog =
"%%%%BeginProlog\n"
"/L { /y2 exch def\n"
"/x2 exch def\n"
"/y1 exch def\n"
"/x1 exch def\n"
"newpath   x1 y1 moveto x2 y2 lineto\n"
"stroke}\n"
"bind def\n"


"/R { /dy exch def\n"
"/dx exch def\n"
"/y exch def\n"
"/x exch def\n"
"newpath\n"
"x y moveto\n"
"dx 0 rlineto\n"
"0 dy rlineto\n"
"dx neg 0 rlineto\n"
"closepath stroke\n"
"} bind def\n"

"/CL {\n"
"/dy exch def\n"
"/dx exch def\n"
"/y exch def\n"
"/x exch def\n"
"newpath\n"
"x y moveto\n"
"dx 0 rlineto\n"
"0 dy rlineto\n"
"dx neg 0 rlineto\n"
"closepath\n"
"clip\n"
"} bind def\n"

"/FR { /dy exch def\n"
"/dx exch def\n"
"/y exch def\n"
"/x exch def\n"
"currentlinewidth 0 setlinewidth newpath\n"
"x y moveto\n"
"dx 0 rlineto\n"
"0 dy rlineto\n"
"dx neg 0 rlineto\n"
"closepath fill setlinewidth\n"
"} bind def\n"

"/GS { gsave } bind  def\n"
"/GR { grestore } bind def\n"

"/SP { showpage } bind def\n"
"/LW { setlinewidth } bind def\n"
"/CF /Courier def\n"
"/SF { /CF exch def } bind def\n"
"/fsize 12 def\n"
"/FS { /fsize exch def fsize CF findfont exch scalefont setfont }def \n"


"/GL { setgray } bind def\n"
"/SRGB { setrgbcolor } bind def\n"

//  color images 

"/CI { GS /py exch def /px exch def /sy exch def /sx exch def\n"
"translate \n"
"sx sy scale px py 8 \n"
"[ px 0 0 py neg 0 py ]\n"
"currentfile /ASCIIHexDecode filter\n false 3"
" colorimage GR\n"
"} bind def\n"

//  gray images 

"/GI { GS /py exch def /px exch def /sy exch def /sx exch def \n"
"translate \n"
"sx sy scale px py 8 \n"


"[ px 0 0 py neg 0 py ]\n"
"currentfile /ASCIIHexDecode filter\n"
"image GR\n"
"} bind def\n"

// single-color bitmask 

"/MI { GS /py exch def /px exch def /sy exch def /sx exch def \n"
"translate \n"
"sx sy scale px py false \n"
"[ px 0 0 py neg 0 py ]\n"
"currentfile /ASCIIHexDecode filter\n"
"imagemask GR\n"
"} bind def\n"


//  path 

"/BFP { newpath moveto }  def\n"
"/BP { newpath } bind def \n"
"/PL { lineto } bind def \n"
"/PM { moveto } bind def \n"
"/MT { moveto } bind def \n"
"/LT { lineto } bind def \n"
"/EFP { closepath fill } bind def\n"  //was:stroke
"/ELP { stroke } bind def\n"  
"/ECP { closepath stroke } bind def\n"  // Closed (loop)
"/LW { setlinewidth } bind def\n"

// ////////////////////////// misc ////////////////
"/TR { translate } bind def\n"
"/CT { concat } bind def\n"
"/RCT { matrix invertmatrix concat} bind def\n"
"/SC { scale } bind def\n"
//"/GPD { currentpagedevice /PageSize get} def\n"

;


static const char * prolog_2 =  // prolog relevant only if lang_level >1

// color image dictionaries
"/CII {GS /inter exch def /py exch def /px exch def /sy exch def /sx exch def \n"
"translate \n"
"sx sy scale\n"
"/DeviceRGB setcolorspace\n"
"/IDD 8 dict def\n"
"IDD begin\n"
"/ImageType 1 def\n"
"/Width px def\n"
"/Height py def\n"
"/BitsPerComponent 8 def\n"
"/Interpolate inter def\n"
"/DataSource currentfile /ASCIIHexDecode filter def\n"
"/MultipleDataSources false def\n"
"/ImageMatrix [ px 0 0 py neg 0 py ] def\n"
"/Decode [ 0 1 0 1 0 1 ] def\n"
"end\n"
"IDD image GR} bind def\n"

// gray image dict 


"/GII {GS /inter exch def /py exch def /px exch def /sy exch def /sx exch def \n"
"translate \n"
"sx sy scale\n"
"/DeviceGray setcolorspace\n"
"/IDD 8 dict def\n"
"IDD begin\n"
"/ImageType 1 def\n"
"/Width px def\n"
"/Height py def\n"
"/BitsPerComponent 8 def\n"

"/Interpolate inter def\n"
"/DataSource currentfile /ASCIIHexDecode filter def\n"
"/MultipleDataSources false def\n"
"/ImageMatrix [ px 0 0 py neg 0 py ] def\n"
"/Decode [ 0 1 ] def\n"
"end\n"
"IDD image GR} bind def\n"

;

static const char * prolog_3 = // prolog relevant only if lang_level >2

// masked color images 
"/CIM {GS /inter exch def /my exch def /mx exch def /py exch def /px exch def /sy exch def /sx exch def \n"
"translate \n"
"sx sy scale\n"
"/DeviceRGB setcolorspace\n"

"/IDD 8 dict def\n"

"IDD begin\n"
"/ImageType 1 def\n"
"/Width px def\n"
"/Height py def\n"
"/BitsPerComponent 8 def\n"
"/Interpolate inter def\n"
"/DataSource currentfile /ASCIIHexDecode filter def\n"
"/MultipleDataSources false def\n"
"/ImageMatrix [ px 0 0 py neg 0 py ] def\n"

"/Decode [ 0 1 0 1 0 1 ] def\n"
"end\n"

"/IMD 8 dict def\n"
"IMD begin\n"
"/ImageType 1 def\n"
"/Width mx def\n"           
"/Height my def\n"
"/BitsPerComponent 1 def\n"
//  "/Interpolate inter def\n"
"/ImageMatrix [ mx 0 0 my neg 0 my ] def\n"
"/Decode [ 1 0 ] def\n"
"end\n"

"<<\n"
"/ImageType 3\n"
"/InterleaveType 2\n"
"/MaskDict IMD\n"
"/DataDict IDD\n"
">> image GR\n"
"} bind def\n"


//  masked gray images 
"/GIM {GS /inter exch def /my exch def /mx exch def /py exch def /px exch def /sy exch def /sx exch def \n"
"translate \n"
"sx sy scale\n"
"/DeviceGray setcolorspace\n"

"/IDD 8 dict def\n"

"IDD begin\n"
"/ImageType 1 def\n"
"/Width px def\n"
"/Height py def\n"
"/BitsPerComponent 8 def\n"
"/Interpolate inter def\n"
"/DataSource currentfile /ASCIIHexDecode filter def\n"
"/MultipleDataSources false def\n"
"/ImageMatrix [ px 0 0 py neg 0 py ] def\n"

"/Decode [ 0 1 ] def\n"
"end\n"

"/IMD 8 dict def\n"

"IMD begin\n"
"/ImageType 1 def\n"
"/Width mx def\n"           
"/Height my def\n"
"/BitsPerComponent 1 def\n"
"/ImageMatrix [ mx 0 0 my neg 0 my ] def\n"
"/Decode [ 1 0 ] def\n"
"end\n"

"<<\n"
"/ImageType 3\n"
"/InterleaveType 2\n"
"/MaskDict IMD\n"
"/DataDict IDD\n"
">> image GR\n"
"} bind def\n"


"\n"
;

// end prolog 


Fl_PSfile_Device::Fl_PSfile_Device(void)
{
  close_cmd_ = 0;
  lang_level_ = 1;
  mask = 0;
  ps_filename_ = NULL;
}

int Fl_PSfile_Device::start_postscript (int pagecount, enum Page_Format format)
//returns 0 iff OK
{
  this->set_current();
  page_format_ = format;
  
  fprintf(output, "%%!PS-Adobe-3.0\n");
  fprintf(output, "%%%%Creator: FLTK\n");
  if(lang_level_>1)
    fprintf(output, "%%%%LanguageLevel: %i\n" , lang_level_);
  if((pages_ = pagecount))
    fprintf(output, "%%%%Pages: %i\n", pagecount);
  else
    fprintf(output, "%%%%Pages: (atend)\n");
  fprintf(output, "%%%%BeginFeature: *PageSize\n" );
  fprintf(output, "%s\n", (format==A4?"A4":"LETTER") );
  fprintf(output, "%%%%EndFeature\n");
  fprintf(output, "%%%%EndComments\n");
  fprintf(output, prolog);
  if(lang_level_ >1)
    fprintf(output, prolog_2);
  if(lang_level_ >2)
    fprintf(output, prolog_3);
  if(lang_level_>=3){
    fprintf(output, "/CS { clipsave } bind def\n");
    fprintf(output, "/CR { cliprestore } bind def\n");
  }else{
    fprintf(output, "/CS { GS } bind def\n");
    fprintf(output, "/CR { GR } bind def\n");
  }
  page_policy_=1;
  
  
  fprintf(output, "%%%%EndProlog\n");
  if(lang_level_>=2)
    fprintf(output,"<< /Policies << /Pagesize 1 >> >> setpagedevice\n");
  
  reset();
  nPages=0;
  return 0;
}

Fl_PSfile_Device::~Fl_PSfile_Device() {
  if (ps_filename_) free(ps_filename_);
}

void Fl_PSfile_Device::recover(){
  color(cr_,cg_,cb_);
  line_style(linestyle_,linewidth_,linedash_);
  font(font_,size_);
}

void Fl_PSfile_Device::reset(){
  gap_=1;
  clip_=0;
  cr_=cg_=cb_=0;
  font_=FL_HELVETICA;
  size_=12;
  linewidth_=0;
  linestyle_=FL_SOLID;
  strcpy(linedash_,"");
  Clip *c=clip_;   ////just not to have memory leaks for badly writen code (forgotten clip popping)
  
  while(c){
    clip_=clip_->prev;
    delete c;
    c=clip_;
  }
  
}

void Fl_PSfile_Device::page_policy(int p){
  page_policy_ = p;
  if(lang_level_>=2)
    fprintf(output,"<< /Policies << /Pagesize %i >> >> setpagedevice\n", p);
}

// //////////////////// paging //////////////////////////////////////////



void Fl_PSfile_Device::page(double pw, double ph, int media) {
  
  if (nPages){
    fprintf(output, "CR\nGR\nGR\nGR\nSP\nrestore\n");
  }
  ++nPages;
  fprintf(output, "%%%%Page: %i %i\n" , nPages , nPages);
  if (pw>ph){
    fprintf(output, "%%%%PageOrientation: Landscape\n");
  }else{
    fprintf(output, "%%%%PageOrientation: Portrait\n");
  }
  
  fprintf(output, "%%%%BeginPageSetup\n");
  if((media & MEDIA) &&(lang_level_>1)){
    int r = media & REVERSED;
    if(r) r = 2;
    fprintf(output, "<< /PageSize [%i %i] /Orientation %i>> setpagedevice\n", (int)(pw+.5), (int)(ph+.5), r);
  }
  fprintf(output, "%%%%EndPageSetup\n");
  
  pw_=pw;
  ph_=ph;
  reset();
  
  fprintf(output, "save\n");
  fprintf(output, "GS\n");
  fprintf(output, "%g %g TR\n", (double)0 /*lm_*/ , ph_ /* - tm_*/);
  fprintf(output, "1 -1 SC\n");
  line_style(0);
  fprintf(output, "GS\n");
  
  if(!((media & MEDIA) &&(lang_level_>1))){
    if(pw>ph)
      if(media & REVERSED)
        fprintf(output, "-90 rotate %i 0 translate\n", int(-pw));
      else
        fprintf(output, "90 rotate 0 %i translate\n", int(-ph));
      else
	if(media & REVERSED)
	  fprintf(output, "180 rotate %i %i translate\n", int(-pw), int(-ph));
  }
  fprintf(output, "GS\nCS\n");
};

void Fl_PSfile_Device::page(int format){
  
  
  if(format &  LANDSCAPE){
    ph_=Fl_PSfile_Device::page_formats[format & 0xFF][0];
    pw_=Fl_PSfile_Device::page_formats[format & 0xFF][1];
  }else{
    pw_=Fl_PSfile_Device::page_formats[format & 0xFF][0];
    ph_=Fl_PSfile_Device::page_formats[format & 0xFF][1];
  }
  page(pw_,ph_,format & 0xFF00);//,orientation only;
};

void Fl_PSfile_Device::rect(int x, int y, int w, int h) {
  // Commented code does not work, i can't find the bug ;-(
  // fprintf(output, "GS\n");
  //  fprintf(output, "%i, %i, %i, %i R\n", x , y , w, h);
  //  fprintf(output, "GR\n");
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x , y);
  fprintf(output, "%i %i LT\n", x+w-1 , y);
  fprintf(output, "%i %i LT\n", x+w-1 , y+h-1);
  fprintf(output, "%i %i LT\n", x , y+h-1);
  fprintf(output, "ECP\n");
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::rectf(int x, int y, int w, int h) {
  fprintf(output, "%g %g %i %i FR\n", x-0.5, y-0.5, w, h);
}

void Fl_PSfile_Device::line(int x1, int y1, int x2, int y2) {
  fprintf(output, "GS\n");
  fprintf(output, "%i %i %i %i L\n", x1 , y1, x2 ,y2);
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::line(int x0, int y0, int x1, int y1, int x2, int y2) {
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x0 , y0);
  fprintf(output, "%i %i LT\n", x1 , y1);
  fprintf(output, "%i %i LT\n", x2 , y2);
  fprintf(output, "ELP\n");
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::xyline(int x, int y, int x1, int y2, int x3){
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x , y );
  fprintf(output, "%i %i LT\n", x1 , y );
  fprintf(output, "%i %i LT\n", x1 , y2);
  fprintf(output,"%i %i LT\n", x3 , y2);
  fprintf(output, "ELP\n");
  fprintf(output, "GR\n");
};


void Fl_PSfile_Device::xyline(int x, int y, int x1, int y2){
  
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x , y);
  fprintf(output,"%i %i LT\n", x1 , y);
  fprintf(output, "%i %i LT\n", x1 , y2 );
  fprintf(output, "ELP\n");
  fprintf(output, "GR\n");
};

void Fl_PSfile_Device::xyline(int x, int y, int x1){
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x , y);
  fprintf(output, "%i %i LT\n", x1 , y );
  fprintf(output, "ELP\n");
  
  fprintf(output, "GR\n");
};

void Fl_PSfile_Device::yxline(int x, int y, int y1, int x2, int y3){
  fprintf(output, "GS\n");
  
  fprintf(output,"BP\n");
  fprintf(output,"%i %i MT\n", x , y);
  fprintf(output, "%i %i LT\n", x , y1 );
  fprintf(output, "%i %i LT\n", x2 , y1 );
  fprintf(output , "%i %i LT\n", x2 , y3);
  fprintf(output, "ELP\n");
  fprintf(output, "GR\n");
};

void Fl_PSfile_Device::yxline(int x, int y, int y1, int x2){
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x , y);
  fprintf(output, "%i %i LT\n", x , y1);
  fprintf(output, "%i %i LT\n", x2 , y1);
  fprintf(output, "ELP\n");
  fprintf(output, "GR\n");
};

void Fl_PSfile_Device::yxline(int x, int y, int y1){
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x , y);
  fprintf(output, "%i %i LT\n", x , y1);
  fprintf(output, "ELP\n");
  fprintf(output, "GR\n");
};

void Fl_PSfile_Device::loop(int x0, int y0, int x1, int y1, int x2, int y2) {
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x0 , y0);
  fprintf(output, "%i %i LT\n", x1 , y1);
  fprintf(output, "%i %i LT\n", x2 , y2);
  fprintf(output, "ECP\n");
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::loop(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x0 , y0);
  fprintf(output, "%i %i LT\n", x1 , y1);
  fprintf(output, "%i %i LT\n", x2 , y2);
  fprintf(output, "%i %i LT\n", x3 , y3);
  fprintf(output, "ECP\n");
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::polygon(int x0, int y0, int x1, int y1, int x2, int y2) {
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x0 , y0);
  fprintf(output,"%i %i LT\n", x1 , y1);
  fprintf(output, "%i %i LT\n", x2 , y2);
  fprintf(output, "EFP\n");
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::polygon(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
  fprintf(output, "GS\n");
  fprintf(output,"BP\n");
  fprintf(output, "%i %i MT\n", x0 , y0 );
  fprintf(output, "%i %i LT\n", x1 , y1 );
  fprintf(output, "%i %i LT\n", x2 , y2 );
  fprintf(output, "%i %i LT\n", x3 , y3 );
  
  fprintf(output, "EFP\n");
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::point(int x, int y){
  rectf(x,y,1,1);
}

static int dashes_flat[5][7]={
{-1,0,0,0,0,0,0},
{3,1,-1,0,0,0,0},
{1,1,-1,0,0,0,0},
{3,1,1,1,-1,0,0},
{3,1,1,1,1,1,-1}
};


//yeah, hack...
static double dashes_cap[5][7]={
{-1,0,0,0,0,0,0},
{2,2,-1,0,0,0,0},
{0.01,1.99,-1,0,0,0,0},
{2,2,0.01,1.99,-1,0,0},
{2,2,0.01,1.99,0.01,1.99,-1}
};


void Fl_PSfile_Device::line_style(int style, int width, char* dashes){
  //line_styled_=1;
  
  linewidth_=width;
  linestyle_=style;
  //dashes_= dashes;
  if(dashes){
    if(dashes != linedash_)
      strcpy(linedash_,dashes);
    
  }else
    linedash_[0]=0;
  char width0 = 0;
  if(!width){
    width=1; //for screen drawing compatability
    width0=1;
  }
  
  fprintf(output, "%i setlinewidth\n", width);
  
  if(!style && (!dashes || !(*dashes)) && width0) //system lines
    style = FL_CAP_SQUARE;
  
  int cap = (style &0xf00) >> 8;
  if(cap) cap--;
  fprintf(output,"%i setlinecap\n", cap);
  
  int join = (style & 0xf000) >> 12;
  
  if(join) join--;
  fprintf(output,"%i setlinejoin\n", join);
  
  
  fprintf(output, "[");
  if(dashes && *dashes){
    while(*dashes){
      fprintf(output, "%i ", *dashes);
      dashes++;
    }
  }else{
    int * ds; 
    if(style & 0x200){ // round and square caps, dash length need to be adjusted
      double *dt = dashes_cap[style & 0xff];
      while (*dt >= 0){
	fprintf(output, "%g ",width * (*dt));
	dt++;
      }
    }else{
      
      ds = dashes_flat[style & 0xff];
      while (*ds >= 0){
	fprintf(output, "%i ",width * (*ds));
        ds++;
      }
    }
  }
  fprintf(output, "] 0 setdash\n");
};

static const char *_fontNames[] = {
"Helvetica",
"Helvetica-Bold",
"Helvetica-Oblique",
"Helvetica-BoldOblique",
"Courier",
"Courier-Bold",
"Courier-Oblique",
"Courier-BoldOblique",
"Times",
"Times-Bold",
"Times-Italic",
"Times-BoldItalic",
"Symbol",
"Courier",
"CourierBold",
"ZapfDingbats"
};
// TODO RK: CRITICAL: this is hacky/temporary implementation of fonts. All below should be replaced.
extern Fl_Display fl_display_device;

void Fl_PSfile_Device::font(int f, int s) {
  
  //fonted_=1;
  if (f >= FL_FREE_FONT)
    f = FL_COURIER;
  fprintf(output, "/%s SF\n" , _fontNames[f]);
  fprintf(output,"%i FS\n", s);
  fl_display_device.font(f,s); //Dirty hack for font measurement ;-(
  font_=f; size_=s;
};

/*double Fl_PSfile_Device::width(unsigned c){
  return fl_display_device.width(c); //Dirty...
}

double Fl_PSfile_Device::width(const char* s, int n){;
  return fl_display_device.width(s,n); //Very Dirty...
}
int Fl_PSfile_Device::descent(){
  return fl_display_device.descent(); //A bit Dirty...
}
int Fl_PSfile_Device::height(){
  return fl_display_device.height(); //Still Dirty...
}*/

void Fl_PSfile_Device::color(Fl_Color c) {
  //colored_=1;
  color_=c;
  Fl::get_color(c, cr_, cg_, cb_);
  if (cr_==cg_ && cg_==cb_) {
    double gray = cr_/255.0;
    fprintf(output, "%g GL\n", gray);
    
  } else {
    double fr, fg, fb;
    fr = cr_/255.0;
    fg = cg_/255.0;
    fb = cb_/255.0;
    fprintf(output,"%g %g %g SRGB\n", fr , fg , fb);
  }
}

void Fl_PSfile_Device::color(unsigned char r, unsigned char g, unsigned char b) {
  
  //colored_=1;
  cr_=r;cg_=g;cb_=b;
  if (r==g && g==b) {
    double gray = r/255.0;
    fprintf(output, "%g GL\n", gray);
  } else {
    double fr, fg, fb;
    fr = r/255.0;
    fg = g/255.0;
    fb = b/255.0;
    fprintf(output, "%g %g %g SRGB\n", fr , fg , fb);
  }
}

void Fl_PSfile_Device::draw(int angle, const char *str, int n, int x, int y)
{
  fprintf(output, "GS %d %d translate %d rotate\n", x, y, - angle);
  this->transformed_draw(str, n, 0, 0);
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::transformed_draw(const char* str, int n, double x, double y){
  
  if (!n||!str||!*str)return;
  fprintf(output, "GS\n");
  fprintf(output,"%g %g moveto\n", x , y);
  fprintf(output, "[1 0 0 -1 0 0] concat\n");
  int i=1;
  fprintf(output, "\n(");
  for(int j=0;j<n;j++){
    if(i>240){
      fprintf(output, "\\\n");
      
      i=0;
    }
    i++;
    switch (*str) {
      case '(': case ')':
        fprintf(output, "\\%c" , *str);
        break;
      default:
        fprintf(output, "%c", *str);
    }
    str++;
  }
  fprintf(output, ") show\n");
  fprintf(output, "GR\n");
}

struct matrix {double a, b, c, d, x, y;};
extern matrix * fl_matrix;

void Fl_PSfile_Device::concat(){
  fprintf(output,"[%g %g %g %g %g %g] CT\n", fl_matrix->a , fl_matrix->b , fl_matrix->c , fl_matrix->d , fl_matrix->x , fl_matrix->y);
}

void Fl_PSfile_Device::reconcat(){
  fprintf(output, "[%g %g %g %g %g %g] RCT\n" , fl_matrix->a , fl_matrix->b , fl_matrix->c , fl_matrix->d , fl_matrix->x , fl_matrix->y);
}

/////////////////  transformed (double) drawings ////////////////////////////////


void Fl_PSfile_Device::begin_points(){
  fprintf(output, "GS\n");
  concat();
  
  fprintf(output, "BP\n");
  gap_=1;
  shape_=POINTS;
};

void Fl_PSfile_Device::begin_line(){
  fprintf(output, "GS\n");
  concat();
  fprintf(output, "BP\n");
  gap_=1;
  shape_=LINE;
};

void Fl_PSfile_Device::begin_loop(){
  fprintf(output, "GS\n");
  concat();
  fprintf(output, "BP\n");
  gap_=1;
  shape_=LOOP;
};

void Fl_PSfile_Device::begin_polygon(){
  fprintf(output, "GS\n");
  concat();
  fprintf(output, "BP\n");
  gap_=1;
  shape_=POLYGON;
};

void Fl_PSfile_Device::vertex(double x, double y){
  if(shape_==POINTS){
    fprintf(output,"%g %g MT\n", x , y);
    gap_=1;
    return;
  }
  if(gap_){
    fprintf(output,"%g %g MT\n", x , y);
    gap_=0;
  }else
    fprintf(output, "%g %g LT\n", x , y);
};

void Fl_PSfile_Device::curve(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3){
  if(shape_==NONE) return;
  if(gap_)
    fprintf(output,"%g %g MT\n", x , y);
  else
    fprintf(output, "%g %g LT\n", x , y);
  gap_=0;
  
  fprintf(output, "%g %g %g %g %g %g curveto \n", x1 , y1 , x2 , y2 , x3 , y3);
};


void Fl_PSfile_Device::circle(double x, double y, double r){
  if(shape_==NONE){
    fprintf(output, "GS\n");
    concat();
    //    fprintf(output, "BP\n");
    fprintf(output,"%g %g %g 0 360 arc\n", x , y , r);
    reconcat();
    //    fprintf(output, "ELP\n");
    fprintf(output, "GR\n");
  }else
    
    fprintf(output, "%g %g %g 0 360 arc\n", x , y , r);
  
};

void Fl_PSfile_Device::arc(double x, double y, double r, double start, double a){
  if(shape_==NONE) return;
  gap_=0;
  if(start>a)
    fprintf(output, "%g %g %g %g %g arc\n", x , y , r , -start, -a);
  else
    fprintf(output, "%g %g %g %g %g arcn\n", x , y , r , -start, -a);
  
};

void Fl_PSfile_Device::arc(int x, int y, int w, int h, double a1, double a2) {
  fprintf(output, "GS\n");
  //fprintf(output, "BP\n");
  begin_line();
  fprintf(output, "%g %g TR\n", x + w/2.0 -0.5 , y + h/2.0 - 0.5);
  fprintf(output, "%g %g SC\n", (w-1)/2.0 , (h-1)/2.0 );
  arc(0,0,1,a2,a1);
  //  fprintf(output, "0 0 1 %g %g arc\n" , -a1 , -a2);
  fprintf(output, "%g %g SC\n", 2.0/(w-1) , 2.0/(h-1) );
  fprintf(output, "%g %g TR\n", -x - w/2.0 +0.5 , -y - h/2.0 +0.5);
  end_line();
  
  //  fprintf(output, "%g setlinewidth\n",  2/sqrt(w*h));
  //  fprintf(output, "ELP\n");
  //  fprintf(output, 2.0/w , 2.0/w , " SC\n";
  //  fprintf(output, (-x - w/2.0) , (-y - h/2)  , " TR\n";
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::pie(int x, int y, int w, int h, double a1, double a2) {
  
  fprintf(output, "GS\n");
  fprintf(output, "%g %g TR\n", x + w/2.0 -0.5 , y + h/2.0 - 0.5);
  fprintf(output, "%g %g SC\n", (w-1)/2.0 , (h-1)/2.0 );
  begin_polygon();
  vertex(0,0);
  arc(0.0,0.0, 1, a2, a1);
  end_polygon();
  fprintf(output, "GR\n");
}

void Fl_PSfile_Device::end_points(){
  gap_=1;
  reconcat();
  fprintf(output, "ELP\n"); //??
  fprintf(output, "GR\n");
  shape_=NONE;
}

void Fl_PSfile_Device::end_line(){
  gap_=1;
  reconcat();
  fprintf(output, "ELP\n");
  fprintf(output, "GR\n");
  shape_=NONE;
}
void Fl_PSfile_Device::end_loop(){
  gap_=1;
  reconcat();
  fprintf(output, "ECP\n");
  fprintf(output, "GR\n");
  shape_=NONE;
}

void Fl_PSfile_Device::end_polygon(){
  
  gap_=1;
  reconcat();
  fprintf(output, "EFP\n");
  fprintf(output, "GR\n");
  shape_=NONE;
}

void Fl_PSfile_Device::transformed_vertex(double x, double y){
  reconcat();
  if(gap_){
    fprintf(output, "%g %g MT\n", x , y);
    gap_=0;
  }else
    fprintf(output, "%g %g LT\n", x , y);
  concat();
};

/////////////////////////////   Clipping /////////////////////////////////////////////

void Fl_PSfile_Device::push_clip(int x, int y, int w, int h) {
  Clip * c=new Clip();
  clip_box(x,y,w,h,c->x,c->y,c->w,c->h);
  c->prev=clip_;
  clip_=c;
  fprintf(output, "CR\nCS\n");
  if(lang_level_<3)
    recover();
  fprintf(output, "%g %g %i %i CL\n", clip_->x-0.5 , clip_->y-0.5 , clip_->w  , clip_->h);
  
}

void Fl_PSfile_Device::push_no_clip() {
  Clip * c = new Clip();
  c->prev=clip_;
  clip_=c;
  clip_->x = clip_->y = clip_->w = clip_->h = -1;
  fprintf(output, "CR\nCS\n");
  if(lang_level_<3)
    recover();
}

void Fl_PSfile_Device::pop_clip() {
  if(!clip_)return;
  Clip * c=clip_;
  clip_=clip_->prev;
  delete c;
  fprintf(output, "CR\nCS\n");
  if(clip_ && clip_->w >0)
    fprintf(output, "%g %g %i %i CL\n", clip_->x - 0.5, clip_->y - 0.5, clip_->w  , clip_->h);
  // uh, -0.5 is to match screen clipping, for floats there should be something beter
  if(lang_level_<3)
    recover();
}

int Fl_PSfile_Device::clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H){
  if(!clip_){
    X=x;Y=y;W=w;H=h;
    return 1;
  }
  if(clip_->w < 0){
    X=x;Y=y;W=w;H=h;
    return 1;
  }
  int ret=0;
  if (x > (X=clip_->x)) {X=x; ret=1;}
  if (y > (Y=clip_->y)) {Y=y; ret=1;}
  if ((x+w) < (clip_->x+clip_->w)) {
    W=x+w-X;
    
    ret=1;
    
  }else
    W = clip_->x + clip_->w - X;
  if(W<0){
    W=0;
    return 1;
  }
  if ((y+h) < (clip_->y+clip_->h)) {
    H=y+h-Y;
    ret=1;
  }else
    H = clip_->y + clip_->h - Y;
  if(H<0){
    W=0;
    H=0;
    return 1;
  }
  return ret;
};

int Fl_PSfile_Device::not_clipped(int x, int y, int w, int h){
  if(!clip_) return 1;
  if(clip_->w < 0) return 1;
  int X, Y, W, H;
  clip_box(x, y, w, h, X, Y, W, H);
  if(W) return 1;
  return 0;
};


void Fl_PSfile_Device::margins(int *left, int *top, int *right, int *bottom) // to implement
{
  if(left) *left = (int)(left_margin / scale_x + .5);
  if(right) *right = (int)(left_margin / scale_x + .5);
  if(top) *top = (int)(top_margin / scale_y + .5);
  if(bottom) *bottom = (int)(top_margin / scale_y + .5);
}

int Fl_PSfile_Device::printable_rect(int *w, int *h)
//returns 0 iff OK
{
  if(w) *w = (int)((pw_ - 2 * left_margin) / scale_x + .5);
  if(h) *h = (int)((ph_ - 2 * top_margin) / scale_y + .5);
  return 0;
}

void Fl_PSfile_Device::origin(int x, int y)
{
  x_offset = x;
  y_offset = y;
  fprintf(output, "GR GR GS %d %d TR  %f %f SC %d %d TR %f rotate GS\n", 
	  left_margin, top_margin, scale_x, scale_y, x, y, angle);
}

void Fl_PSfile_Device::scale (float s_x, float s_y)
{
  scale_x = s_x;
  scale_y = s_y;
  fprintf(output, "GR GR GS %d %d TR  %f %f SC %f rotate GS\n", 
	  left_margin, top_margin, scale_x, scale_y, angle);
}

void Fl_PSfile_Device::rotate (float rot_angle)
{
  angle = - rot_angle;
  fprintf(output, "GR GR GS %d %d TR  %f %f SC %d %d TR %f rotate GS\n", 
	  left_margin, top_margin, scale_x, scale_y, x_offset, y_offset, angle);
}

void Fl_PSfile_Device::translate(int x, int y)
{
  fprintf(output, "GS %d %d translate GS\n", x, y);
}

void Fl_PSfile_Device::untranslate(void)
{
  fprintf(output, "GR GR\n");
}

int Fl_PSfile_Device::start_page (void)
{
  page(page_format_);
  x_offset = 0;
  y_offset = 0;
  scale_x = scale_y = 1.;
  left_margin = 30;
  top_margin = 30;
  angle = 0;
  fprintf(output, "GR GR GS %d %d translate GS\n", left_margin, top_margin);
  return 0;
}

int Fl_PSfile_Device::end_page (void)
{
  return 0;
}

int Fl_PSfile_Device::start_job (int pagecount, enum Page_Format format, int *frompage, int *topage)
{
  Fl_Native_File_Chooser fnfc;
  fnfc.title("Create a .ps file");
  fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
  fnfc.filter("PostScript\t*.ps\n");
  // Show native chooser
  if ( fnfc.show() ) return 1;
  output = fopen(fnfc.filename(), "w");
  if(output == NULL) return 1;
  ps_filename_ = strdup(fnfc.filename());
  if(frompage) *frompage = 1;
  if(topage) *topage = pagecount;
  return start_postscript(pagecount, format);
}

void Fl_PSfile_Device::end_job (void)
// finishes PostScript & closes file
{
  if (nPages) {  // for eps nPages is 0 so it is fine ....
    fprintf(output, "CR\nGR\nGR\nGR\nSP\n restore\n");
    if (!pages_){
      fprintf(output, "%%%%Trailer\n");
      fprintf(output, "%%%%Pages: %i\n" , nPages);
    };
  } else
    fprintf(output, "GR\n restore\n");
  fprintf(output, "%%%%EOF");
  reset();
  fclose(output);
  
  while (clip_){
    Clip * c= clip_;
    clip_= clip_->prev;
    delete c;
  }
  if (close_cmd_) (*close_cmd_)(output);
  current_display()->set_current();
}

#if ! (defined(__APPLE__) || defined(WIN32) )
int Fl_PS_Printer::start_job(int pages, int *firstpage, int *lastpage) {
  // TODO should start a print dialog and return the selected paper format and the temp .ps file
  // and desired page range
  return Fl_PSfile_Device::start_job(pages,A4,firstpage,lastpage); 
}

void Fl_PS_Printer::end_job(void)
{
  Fl_PSfile_Device::end_job(); 
  // TODO should print the ps_filename_ file
}

#endif
