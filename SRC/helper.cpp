#include "helper.h"
#define ONE_MINUTE 60000

//find the coefficient using the user set timer minutes
double get_coefficient( int total_minutes ) {
  double coefficient = 0.0;
  coefficient = 255 / pow( (double)total_minutes, 2.0 );
  return coefficient;
}

//find alpha value at specific minutes using coefficient
Uint8 get_alpha( int minutes, double coefficient ) {
  Uint8 alpha = 0;
  alpha = ceil( coefficient * pow( minutes, 2 ) );
  if ( alpha <= 255 ) {
    return alpha;   //make sure that alpha is 255 or lower
  }
  else {
    return alpha = 255;
  }
}

//start the break, TODO:release keyboard and mouse control;
bool start_break( bool short_break, unsigned short_length, unsigned long_length, Timer *countdown ) {
  if ( full_screen ){
    SDL_SetWindowFullscreen( g_window, 0 );     //go into windowed mode
    full_screen = false;

    if( !background_texture.load_from_file( "img/vancouver_1280.jpg" ) ) {    //load windowed background
      printf( "Failed to load background texture 1280.\n" );
    }
    else {
      if ( !text_overlay.load_from_file( "img/restart_timer_1280.png" ) ) {
        printf( "Failed to load restart_timer_1280 overlay.\n" );     //load windowed overlay
      }
      //set callback to start alarm sound and start countdown timer
      if ( short_break ) {
        countdown->start_countdown( short_length );
        SDL_TimerID break_alarm = SDL_AddTimer( short_length * 60000 , alarm_callback, NULL);
      }
      else {
        countdown->start_countdown( long_length );
        SDL_TimerID break_alarm = SDL_AddTimer( long_length * 60000, alarm_callback, NULL);
      }
      //break started
      return true;
    }
  }
  else {
    printf( "Error: Cannot start break\n" );
    return false;
  }
}

//end the break or start studying TODO: something to remove the timers
bool end_break( bool short_break ) {
  if ( !full_screen ) {
    SDL_SetWindowFullscreen( g_window, SDL_WINDOW_FULLSCREEN_DESKTOP );
    full_screen = true;

    if (!background_texture.load_from_file( "img/vancouver_1920.jpg" ) ) {
      printf( "Failed to load background texture 1920.\n" );
    }
    else {
      if ( short_break ) {
        //load short break overlay
        if ( !text_overlay.load_from_file( "img/shortbreak_1920.png" ) ) {
          printf( "Failed to load shortbreak_1920.png.\n" );
        }
      }
      else if ( !short_break ) {
        //load long break overlay
        if ( !text_overlay.load_from_file( "img/longbreak_1920.png" ) ) {
          printf( "Failed to load longbreak_1920.png.\n" );
        }
      }
      //set overlay to be fully transparent at start of study
      text_overlay.set_alpha( 0 );
      //start minute timer for getalpha
      SDL_TimerID count_down = SDL_AddTimer( ONE_MINUTE, count_down_callback, NULL );

      return true;
    }
  }
  else {
    printf( "Error: Cannot start studying\n" );
    return false;
  }
}

//function to render scren
void render_screen() {
  //clear screen
  SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear( g_renderer );

  //render frame
  background_texture.render( 0, 0 );
  text_overlay.render( 0, 0 );

  //render text
  timer_outline_texture.render( ( SCREEN_WIDTH - timer_texture.get_width() ) / 2, ( SCREEN_HEIGHT - timer_texture.get_height() ) / 2 );
  timer_texture.render( ( SCREEN_WIDTH - timer_texture.get_width() ) / 2, ( SCREEN_HEIGHT - timer_texture.get_height() ) / 2 );

  //update screen
  SDL_RenderPresent( g_renderer );
}

//function to load settings from settings.txt
void load_settings( unsigned *study_length, unsigned *short_length, unsigned *long_length, bool *hardcore ) {
  FILE *settings = NULL;
  if ( (settings = fopen( "settings.txt", "r")) == NULL ) {
    //if file does not exisit create default file
    printf("No settings.txt, create default file with default values\n" );
    settings = fopen( "settings.txt", "w");
    fprintf( settings, "Study period in mintues (max: 60)\nStudy Length: 25\nBreak length in minutes (max: 60)\nShort break: 5\nLong break: 10\nHardcore mode forces timer completion (on/off)\nHardcore: off\n" );
    *study_length = 25;
    *short_length = 5;
    *long_length = 10;
    *hardcore = false;
    return;
  }
  else {
    //read settings from file and assign
    unsigned length = 60;     //max line length
    char line[length];
    char temp[length];
    char off[] = "off";
    char on[] = "on";

    fgets( line, length, settings );      //skips first line

    fgets( line, length, settings );
    sscanf( line, "%*s %*s %s", temp );   //parse study length period
    *study_length = (unsigned)(strtol(temp, NULL, 10));

    fgets( line, length, settings );      //skips third line

    fgets( line, length, settings );
    sscanf( line, "%*s %*s %s", temp );   //parse short break length into temp
    *short_length = (unsigned)(strtol(temp, NULL, 10));

    fgets( line, length, settings );
    sscanf( line, "%*s %*s %s", temp );   //parse long break length into temp
    *long_length = (unsigned)(strtol(temp, NULL, 10));

    fgets( line, length, settings );      //skips fourth line

    fgets( line, length, settings );
    sscanf( line, "%*s %s", temp );
    if ( !strcmp( temp, on ) ) {          //check for hardcore mode
      *hardcore = true;
    }
    else if ( !strcmp( temp, off ) ) {
      *hardcore = false;
    }
    else {
      //if can't parse set default
      printf( "Default: setting hardcore mode to off\n" );
      *hardcore = false;
    }
    return;
  }
}

//call backfunction for timer, pushing ONE_MINUTE into event queue
//also cause callback to be called again at one minute
Uint32 count_down_callback( Uint32 interval, void *param ) {
  SDL_Event event;
  SDL_UserEvent userevent;

  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = NULL;
  userevent.data2 = NULL;

  event.type = SDL_USEREVENT;
  event.user = userevent;

  SDL_PushEvent(&event);
  return(interval);
}

//callback function to start ringing the alarm *async*
Uint32 alarm_callback( Uint32 interval, void *param ) {
  Mix_PlayChannel( -1, alarm_sound, -1 );    //play alarm sound loop infinitely
  return 0;
}
