with import <nixpkgs> {}; {
  projectEnv = stdenv.mkDerivation {
    name = "ncurses";
    buildInputs = [stdenv freetype];
    propagateBuildInputes = [ncurses];
  };
}

