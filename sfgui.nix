# sfgui.nix
{ pkgs ? import <nixpkgs> {}, ... }:

pkgs.stdenv.mkDerivation {
  name = "SFGUI";
  src = ./third_party/SFGUI;

  nativeBuildInputs = [ pkgs.cmake pkgs.pkg-config ];
  buildInputs = [ pkgs.sfml pkgs.mesa pkgs.libGLU pkgs.xorg.libX11 ];

  buildPhase = ''
    cmake .
    make
  '';
}

