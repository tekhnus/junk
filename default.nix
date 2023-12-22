{ pkgs ? import <nixpkgs> {} }:

let
  sfgui = import ./sfgui.nix {};
  box2d = import ./box2d.nix {};
in
pkgs.stdenv.mkDerivation {
  name = "junk";
  src = pkgs.lib.cleanSource ./.;

  nativeBuildInputs = [ pkgs.cmake pkgs.pkg-config ];
  buildInputs = [ pkgs.stdenv.cc pkgs.cmake pkgs.boost pkgs.sfml sfgui pkgs.mesa pkgs.libGLU pkgs.xorg.libX11 box2d pkgs.libevent pkgs.thrift ];

  cmakeFlags = [
    "-DBOOST_ROOT=${pkgs.boost}"
    "-DCMAKE_INSTALL_PREFIX=$out"
  ];

  configurePhase = ":";

  buildPhase = ''
    ls -R ${pkgs.box2d}
    cmake . $cmakeFlags
    make
  '';
}

