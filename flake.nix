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
              sfgui = import ./third_party/sfgui.nix { inherit pkgs; };
              box2d = import ./third_party/box2d.nix { inherit pkgs; };
            })
          ];
        };
        stdenv = pkgs.clangStdenv;
      in
      rec {
        packages.default = stdenv.mkDerivation {
          name = "junk";
          src = pkgs.lib.cleanSource ./.;
          nativeBuildInputs = [
            pkgs.cmake
            pkgs.pkg-config
            pkgs.ninja
          ];
          buildInputs = [
            pkgs.boost
            pkgs.sfml
            pkgs.mesa
            pkgs.sfgui
            pkgs.libGLU
            pkgs.xorg.libX11
            pkgs.box2d
            pkgs.thrift
          ];
        };
        devShells.default = pkgs.mkShell.override { inherit stdenv; } {
          nativeBuildInputs = [
            pkgs.clang-tools_17
            pkgs.fd
            pkgs.moreutils
            pkgs.python3
            pkgs.cmake
            pkgs.pkg-config
            pkgs.ninja
          ];
          hardeningDisable = [ "fortify" ];
          inputsFrom = [ packages.default ];
        };
      });
}
