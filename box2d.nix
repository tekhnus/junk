# box2d.nix
{ pkgs ? import <nixpkgs> { }, ... }:

pkgs.stdenv.mkDerivation {
  name = "box2d";
  src = ./third_party/box2d;

  nativeBuildInputs = [ pkgs.cmake pkgs.pkg-config ];
  buildInputs = [
    pkgs.xorg.libX11
    pkgs.xorg.libXrandr
    pkgs.xorg.libXinerama
    pkgs.xorg.libXcursor
    pkgs.xorg.libXi
    pkgs.darwin.apple_sdk.frameworks.Carbon
    pkgs.darwin.apple_sdk.frameworks.Cocoa
    pkgs.darwin.apple_sdk.frameworks.Kernel
  ];

  buildPhase = ''
    cmake .
    make
  '';
}

