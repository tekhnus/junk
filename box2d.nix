# box2d.nix
{ pkgs ? import <nixpkgs> {}, ... }:

pkgs.stdenv.mkDerivation {
  name = "box2d";
  src = ./third_party/box2d;

  nativeBuildInputs = [ pkgs.cmake pkgs.pkg-config ];
  buildInputs = [ pkgs.xorg.libX11 pkgs.xorg.libXrandr pkgs.xorg.libXinerama pkgs.xorg.libXcursor pkgs.xorg.libXi ];

  buildPhase = ''
    cmake .
    make
  '';
}

