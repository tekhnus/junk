#include "HUD.hpp"

namespace junk {

void HUD::addState(std::string name, sfg::Delegate delegate) {
  bindings[name] = delegate;
}

sfg::Delegate HUD::getEvent(std::string name) {
  return bindings[name];
}

}  // namespace junk