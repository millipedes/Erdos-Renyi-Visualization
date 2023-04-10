with import <nixpkgs> {}; {
  projectEnv = stdenv.mkDerivation {
    name = "ncurses";
    buildInputs = [stdenv freetype libpng];
    propagateBuildInputes = [ncurses];
  };
}

