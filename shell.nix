{ pkgs ? import <nixpkgs> {} }:

let llvm = pkgs.llvmPackages_12;
	clang = llvm.clang;
	clangd = pkgs.writeScriptBin "clangd" ''
	    #!${pkgs.stdenv.shell}
		export CPATH="$(${clang}/bin/clang -E - -v <<< "" \
			|& ${pkgs.gnugrep}/bin/grep '^ /nix' \
			|  ${pkgs.gawk}/bin/awk 'BEGIN{ORS=":"}{print substr($0, 2)}' \
			|  ${pkgs.gnused}/bin/sed 's/:$//')"
		export CPLUS_INCLUDE_PATH="$(${clang}/bin/clang++ -E - -v <<< "" \
			|& ${pkgs.gnugrep}/bin/grep '^ /nix' \
			|  ${pkgs.gawk}/bin/awk 'BEGIN{ORS=":"}{print substr($0, 2)}' \
			|  ${pkgs.gnused}/bin/sed 's/:$//')"
	    ${llvm.clang-unwrapped}/bin/clangd
	'';

in pkgs.mkShell {
	buildInputs = with pkgs; [
		clangd
		clang
		ccls
		gdb
		gnumake
		asio
		nodejs-16_x
		nodePackages.typescript
		nodePackages.typescript-language-server
	];

	# Permit -O0.
	hardeningDisable = [ "fortify" ];
}
