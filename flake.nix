{
  description = "Junk";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-darwin" ] (system:
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
      rec {
        packages.default = pkgs.stdenv.mkDerivation {
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
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = [ pkgs.lldb ];
          inputsFrom = [ packages.default ];
        };
      });
}
