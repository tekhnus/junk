# sfgui.nix
{ pkgs ? import <nixpkgs> { }, ... }:

pkgs.stdenv.mkDerivation {
  name = "SFGUI";
  src = ./SFGUI;

  nativeBuildInputs = [ pkgs.cmake pkgs.pkg-config ];
  buildInputs = [
    pkgs.sfml
    pkgs.mesa
    pkgs.libGLU
    pkgs.xorg.libX11
  ];
  propagatedBuildInputs = pkgs.lib.optionals
    # Without the following an error happens during find_package(SFGUI).
    # This feels wrong.
    pkgs.stdenv.isDarwin
    [
      pkgs.darwin.apple_sdk.frameworks.OpenGL
    ];
  buildPhase = ''
    cmake .
    make
  '';
}

