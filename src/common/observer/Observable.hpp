/* 
 * File:   Observable.hpp
 * Author: iiotep9huy
 *
 * Created on October 28, 2012, 6:34 PM
 */

#pragma once

#include <unordered_map>

#include <sigc++/sigc++.h>


class Observable
{
public:
  Observable();
  Observable(const Observable& orig);

  virtual ~Observable();

  template<typename Slot>
  void subscribe(std::string signalName, Slot slot)
  {
    //signal::
    sigc::signal_base sigb;

    signal[signalName].connect(slot);
  }

private:
  std::map<std::string, sigc::signal> signal;

protected:
  /*
  void addSignal(string name, sigc::signal)
   {
   
   }
   */

}; // Observable
