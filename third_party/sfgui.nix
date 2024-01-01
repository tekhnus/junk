# sfgui.nix
{ pkgs ? import <nixpkgs> { }, ... }:

pkgs.stdenv.mkDerivation {
  name = "SFGUI";
  src = ./SFGUI;

  nativeBuildInputs = [ pkgs.cmake ];
  buildInputs = [
    pkgs.sfml
  ]
  # SFGUI uses SFML/OpenGL.h, so it must
  # link OpenGL itself.
  ++ pkgs.lib.optionals
    pkgs.stdenv.isDarwin
    [
      pkgs.darwin.apple_sdk.frameworks.OpenGL
    ]
  ++ pkgs.lib.optionals
    pkgs.stdenv.isLinux
    [
      pkgs.libGL
      pkgs.xorg.libX11
    ];

  cmakeFlags = [
    "-DSFGUI_BUILD_EXAMPLES=OFF"
  ];

  buildPhase = ''
    cmake .
    make
  '';
}

