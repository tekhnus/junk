# sfgui.nix
{ pkgs ? import <nixpkgs> { }, ... }:

pkgs.stdenv.mkDerivation {
  name = "SFGUI";
  src = ./SFGUI;

  nativeBuildInputs = [ pkgs.cmake ];
  buildInputs = [
    pkgs.sfml
  ] ++ pkgs.lib.optionals
    pkgs.stdenv.isDarwin
    [
      # SFGUI uses SFML/OpenGL.h, so it must
      # link OpenGL itself.
      pkgs.darwin.apple_sdk.frameworks.OpenGL
    ];
  buildPhase = ''
    cmake .
    make
  '';
}

