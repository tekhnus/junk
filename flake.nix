{
  description = "Your project description";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, ... }:
    let
      pkgs = import nixpkgs {
        system = "x86_64-linux";
        overlays = [
          (self: super: {
            sfgui = import ./sfgui.nix { inherit pkgs; };
            box2d = import ./box2d.nix { inherit pkgs; };
          })
        ];
      };
    in
    {
      packages."x86_64-linux".default = pkgs.stdenv.mkDerivation {
        name = "junk";
        src = pkgs.lib.cleanSource ./.;
        nativeBuildInputs = [
          pkgs.cmake
          pkgs.pkg-config
        ];

        buildInputs = [
          pkgs.stdenv.cc
          pkgs.boost
          pkgs.sfml
          pkgs.mesa
          pkgs.sfgui
          pkgs.libGLU
          pkgs.xorg.libX11
          pkgs.box2d
          pkgs.libevent
          pkgs.thrift
        ];

        cmakeFlags = [
          "-DBOOST_ROOT=${pkgs.boost}"
        ];
      };
      # devShell = pkgs.mkShell {
      #   inputsFrom = [ packages.junk ];
      # };
    };
}
