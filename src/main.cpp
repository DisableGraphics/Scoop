#include "gtkmm/headerbar.h"
#include <cstring>
#include <gtkmm.h>
#include <webkit2/webkit2.h>
#include <filesystem>
#include "strnatcmp.hpp"
#include <iostream>

/* COMPILE WITH:
*  g++ main.cc `pkg-config gtkmm-3.0 --libs --cflags` `pkg-config webkit2gtk-4.0 --libs --cflags` -std=c++1
*/

std::string path;

std::vector<std::string> filesInFolder{};
int position{-1};
std::string file, folder;

void setPosition(std::vector<std::string>ListOfFiles){
  sort(ListOfFiles.begin(), ListOfFiles.end(), compareNat);
  for(int i{0}; i < ListOfFiles.size(); i++){
    if(ListOfFiles[i] == file){
      position = i;
    }
  }
}

std::vector<std::string> getFilesInFolder(std::string folda){
  std::vector<std::string> toReturn; //This is the returned vector
  for (const auto & entry : std::filesystem::directory_iterator(folda)){ //For every file or folder that you find, iterate the folder
    if(!std::filesystem::is_directory(entry)){ //If it's a directory, then no
    if(entry.path().extension() == ".jpg" || entry.path().extension() == ".png" || entry.path().extension() == ".webp" || entry.path().extension() == ".jfif" || entry.path().extension() == ".jpeg" || entry.path().extension() == ".gif")
        toReturn.push_back(entry.path()); //Add the path to the vector
    }
  }
  std::sort(toReturn.begin(), toReturn.end(), compareNat/*, is_less_ordinal*/); //And now sort it with the above filter
  return toReturn;
}

void setFolder(std::string filename){
  std::string tmp{""};
  int pos{0};
  for(int i{static_cast<int>(filename.size())}; i > 0; i--){
    if(filename[i] == '/'){
      pos = i;
      break;
    }
  }
  for(int i{0}; i < pos; i++){
    tmp += filename[i];
  }
  folder = tmp;
}

void openFile(int position, WebKitWebView * webView)
{
  file = filesInFolder[position];
  std::string page{"file://" + file};
  char  char_page[page.size()];
  strcpy(char_page, page.c_str());

  webkit_web_view_load_uri(webView, char_page); //The webView loads the page

  //webkit_web_view_reload(webView); //The webView reloads the page, since it will use a cached one otherwise

  setFolder(file);
}

static void next(WebKitWebView * webView){
  if(position != -1){
    std::vector<std::string> toCount{getFilesInFolder(folder)};
    try{
      position++;
      if(position < toCount.size() && position >= 0){
        openFile(position, webView);
      } else {
        position = 0;
        openFile(position, webView);
      }
    } catch (std::bad_alloc& ba){
      
      openFile(0, webView);
    }
  }
}

//Loads the previous chapter
static void previous(WebKitWebView * webView){
  if(position != -1){
    std::vector<std::string> toCount{getFilesInFolder(folder)};
    try{
      position--;
      if(position >= 0 && position < toCount.size()){
        openFile(position, webView);
      } else {
        position = toCount.size() -1;
        openFile(position, webView);
      }
    } catch (std::bad_alloc& ba){
      openFile(toCount.size() - 1, webView);
    }
  }
}

bool on_input(GdkEventKey* event, WebKitWebView* webView){
  switch(event->keyval)
  {
    case GDK_KEY_period:
      next(webView);
      break;
    case GDK_KEY_comma:
      previous(webView);
      break;
  }
  return true;
}

int main( int argc, char **argv)
{
  path = std::filesystem::current_path(); //Gets the current path
  
  int nullargc{0};
  char ** nullargv = {};
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( nullargc, nullargv, "" );
  Gtk::HeaderBar titleBar;

  Gtk::Window window;
  window.set_default_size( 320, 240 );
  window.set_titlebar(titleBar);
  titleBar.set_title("Imaga");
  titleBar.set_show_close_button();

  WebKitWebView * one =  WEBKIT_WEB_VIEW( webkit_web_view_new() );
  /*
   * the next line does some tricks :
   * GTK_WIDGET( one ) -> convert WebKitWebView to GtkWidget (one->two)
   * Glib::wrap( GTK_WIDGET( one ) ) -> convert GtkWidget to Gtk::Widget (two->three)
   */
  Gtk::Widget * three = Glib::wrap( GTK_WIDGET( one ) );

  window.add( *three );

  std::string header{"file://"};
  std::string argvs(argv[1]);
  std::string uri = header + argvs;
  char uriArr[uri.size()];
  strcpy(uriArr, uri.c_str());
  setFolder(argvs);
  file = argvs;
  webkit_web_view_load_uri(one, uriArr);
    
  filesInFolder = getFilesInFolder(folder);
  setPosition(filesInFolder);

  window.signal_key_press_event().connect(sigc::bind<WebKitWebView*>(sigc::ptr_fun(&on_input), one));

  window.show_all();

  app->run( window );
  exit( 0 );
}

