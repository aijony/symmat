(TeX-add-style-hook
 "proposal"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("revtex4-1" "aps" "prl" "reprint" "groupedaddress" "nofootinbib")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("biblatex" "backend=bibtex" "annotation=true" "style=verbose")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "revtex4-1"
    "revtex4-110"
    "tikz-cd"
    "hyperref"
    "lipsum"
    "biblatex")
   (LaTeX-add-labels
    "sec:orgb355bbc"
    "sec:orgbe592dd"
    "sec:orgb4f4658"
    "sec:org5a2f617"
    "sec:orgecd57bb"
    "sec:orgd9a6b5f"
    "sec:org26344dd"
    "sec:orgbf08b9f"
    "sec:org476deb8"
    "sec:org74372d0"
    "sec:org8957a06"
    "sec:org0386ff9"
    "sec:org63b55e6"
    "sec:org9144e37")
   (LaTeX-add-bibliographies
    "bibl"))
 :latex)

