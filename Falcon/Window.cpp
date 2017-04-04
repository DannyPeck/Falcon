//
//  Window.cpp
//  Falcon
//
//  Created by Danny Peck on 4/2/17.
//  Copyright © 2017 Danny Peck. All rights reserved.
//

#include "Window.h"
#include "SDL_Exception.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// default constructor
Window::Window (std::string title)
: Window (title,
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          SCREEN_WIDTH,
          SCREEN_HEIGHT)
{

}

// initializer constructor
Window::Window (std::string title, int x, int y, int width, int height)
: title_ (title),
x_ (x >= 0 ? x : SDL_WINDOWPOS_UNDEFINED),
y_ (y >= 0 ? y : SDL_WINDOWPOS_UNDEFINED),
width_ (width > 0 ? width : SCREEN_WIDTH),
height_ (height > 0 ? height : SCREEN_HEIGHT),
window_ (nullptr),
renderer_ (nullptr),
screen_ (nullptr)
{
  SDL_Window * window = SDL_CreateWindow (this->title_.c_str (),
                                          this->x_,
                                          this->y_,
                                          this->width_,
                                          this->height_,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (window != nullptr)
  {
    this->window_ = window;
  }
  else
  {
    throw SDL_Exception (SDL_GetError ());
  }

  this->screen_ = SDL_GetWindowSurface (window);

  // Fill the surface white
  SDL_FillRect (this->screen_, nullptr, SDL_MapRGB (this->screen_->format, 0xFF, 0xFF, 0xFF));

  this->renderer_ = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
  
  this->update ();
}

// destructor
Window::~Window (void)
{
  SDL_DestroyWindow (this->window_);
  this->window_ = nullptr;
}

// updates the window
void Window::update (void)
{
  SDL_UpdateWindowSurface (this->window_);
  SDL_FillRect (this->screen_, NULL, 0xFFFFFF);
}

SDL_Renderer * Window::getRenderer (void) const
{
  return this->renderer_;
}

SDL_Surface * Window::getScreen (void) const
{
  return this->screen_;
}

std::string Window::getTitle (void) const
{
  return this->title_;
}

void Window::setTitle (std::string title)
{
  SDL_SetWindowTitle (this->window_, title.c_str ());
  this->title_ = title;
}

int Window::getWidth (void) const
{
  return this->width_;
}

void Window::hide (void)
{
  SDL_HideWindow (this->window_);
}

void Window::show (void)
{
  SDL_ShowWindow (this->window_);
}
