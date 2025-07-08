# AISEC Report Package

Latex package (/w template) for AISEC reports.

## Included Files

- aisec_logo.pdf --- Fraunhofer AISEC logo
- aisecreport.cls --- The report class file
- document.pdf --- Compiled example
- document.tex --- Example TEX file
- README.md --- This readme file

## Installation

1. Create the directory: `$HOME/texmf/tex/latex/aisecreport`
2. Copy the following files to that directory:
    - aisec_logo.pdf
    - aisecreport.cls
3. Run `sudo texhash`

## Usage

The documentclass has to be set to `aisecreport`. The file can then be compiled
with `pdflatex document.tex`.

The theme also uses the Fraunhofer font Frutiger, which has to be installed and
then loaded with `\usepackage{fhgfont}`. The font can be found in the
`frutiger` dictionary of this repository.

## Class Options

The following class options are available:

### No Indent

Usage: `noindent`

This option produces a non-indented version of the report. Only use this option
when really needed, as it breaks the corporate design.

### Confidentiality Markings

Usage: `public`, `restricted`, `confidential` or `strictlyconfidential`

These options mark the document for public use, restricted use, as confidential or as
strictly confidential. Using one of these options prints markings on every page of the
document.

Also, your document should append this classification to it's jobname (`latexmk -jobname ...`).
For more details see [AISEC ISM wiki](https://intern.aisec.fraunhofer.de/display/ISMS/Informationsklassifizierung)
and [OA 2022/11/2B/O](https://ocs.zv.fraunhofer.de/OTCS/livelink.exe/open/408035).

## Recent Updates

Package scrpage2 in aisecreport.cls was changed to scrlayer-scrpage due to debrecation. Source: https://www.komascript.de/faq_scrpage2  (last seen 2020 04 27).
