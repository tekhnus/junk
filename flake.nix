{
  description = "junk";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
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
            pkgs.ninja
          ];
          buildInputs = [
            pkgs.boost
            pkgs.sfml
            pkgs.sfgui
            pkgs.box2d
            pkgs.thrift
          ];
        };
        devShells.default = pkgs.mkShell.override { inherit stdenv; } {
          inputsFrom = [ packages.default ];
          packages = [
            pkgs.python3
            pkgs.clang-tools_17
            pkgs.moreutils
            pkgs.fd
          ];
          hardeningDisable = [ "fortify" ];
        };
      });
}
