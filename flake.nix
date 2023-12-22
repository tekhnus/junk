{
  description = "Your project description";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... } @ inputs:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            (self: super: {
              sfgui = import ./sfgui.nix { inherit pkgs; };
              box2d = import ./box2d.nix { inherit pkgs; };
            })
          ];
        };
      in
      {
        devShell = pkgs.mkShell {
          nativeBuildInputs = [
            pkgs.cmake
            pkgs.pkg-config
            # Other dependencies
          ];

          buildInputs = [
            pkgs.stdenv.cc
            pkgs.boost
            pkgs.sfml
            pkgs.mesa
pkgs.sfgui pkgs.libGLU pkgs.xorg.libX11 pkgs.box2d pkgs.libevent pkgs.thrift ];

          cmakeFlags = [
            "-DBOOST_ROOT=${pkgs.boost}"
          ];
        };
      }
    );
}
