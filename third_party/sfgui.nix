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

  cmakeFlags = [
    "-DSFGUI_BUILD_EXAMPLES=OFF"
  ];

  buildPhase = ''
    cmake .
    make
  '';
}

