# box2d.nix
{ pkgs ? import <nixpkgs> { }, ... }:

pkgs.stdenv.mkDerivation {
  name = "box2d";
  src = ./box2d;

  nativeBuildInputs = [ pkgs.cmake ];

  cmakeFlags = [
    "-DBOX2D_INSTALL=ON"
    "-DBOX2D_BUILD_SHARED=ON"
    "-DBOX2D_BUILD_EXAMPLES=OFF"
    "-DBOX2D_BUILD_TESTBED=OFF"
  ];

  buildPhase = ''
    cmake .
    make
  '';
}
