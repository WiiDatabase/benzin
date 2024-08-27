{
  description = "A Wii Channel banner creator and simulator";

  inputs = {
    nixpkgs = {
      url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    };
  };

  outputs = { self, nixpkgs }:
    let
      forAllSystems = function:
        nixpkgs.lib.genAttrs [
          "x86_64-linux"
          "aarch64-linux"
          "x86_64-darwin"
          "aarch64-darwin"
        ]
          (system: function nixpkgs.legacyPackages.${system});

      version =
        if (self ? shortRev)
        then self.shortRev
        else "dev";
    in
    {

      devShells = forAllSystems
        (pkgs: {
          default = pkgs.mkShell {
            inputsFrom = [ self.packages.${pkgs.system}.default ];

            shellHook = ''
              echo 'Run `substituteInPlace Makefile --replace-fail gcc "$CC"` before building.'
            '';
          };
        });

      packages = forAllSystems
        (pkgs: {
          default = pkgs.stdenv.mkDerivation {
            pname = "benzin";
            inherit version;
            src = pkgs.lib.cleanSource self;

            nativeBuildInputs = [ pkgs.minixml ];

            postPatch = ''
              substituteInPlace Makefile --replace-fail gcc "$CC"
            '';

            installPhase = ''
              runHook preInstall

              install -Dm755 benzin $out/bin/benzin

              runHook postInstall
            '';

            meta = {
              description = "A Wii Channel banner creator and simulator";
              homepage = "https://github.com/WiiDatabase/benzin";
              license = pkgs.lib.licenses.unfree;
              platforms = pkgs.lib.platforms.darwin ++ pkgs.lib.platforms.linux;
            };
          };
        });

    };
}
