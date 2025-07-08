\ProvidesClass{aisecreport}
       [2006/06/13 v0.1 LaTeX document class for
       Fraunhofer AISEC CD-like documents.]
\NeedsTeXFormat{LaTeX2e}

% Based on KOMA-Script scrreprt class
\LoadClass[12pt,chapterprefix=false,parskip=half]{scrreprt}

\RequirePackage{iftex}
\RequirePackage{xstring} % for \jobname checking
\RequirePackage{lastpage} % for total number of pages in footer


\ifluatex
  \RequirePackage{fontspec}
  \setmainfont[
    UprightFont={*-Light},
    % In pdftex, captions are roman by default and need to be redefined to be the light font shape used in the rest of the Document.
    % With fontspec, this light variant however is not set by default and has no shorthand version; so we need to set the fontshape l/n manually.
    FontFace={l}{n}{*-Light},
    FontFace={l}{it}{*-LightItalic},
    BoldFont={*-Bold},
    ItalicFont={*-LightItalic},
    BoldItalicFont={*-BoldItalic},
    Scale=0.917
  ]{FrutigerLTCom}

  \setsansfont[
    UprightFont={*-Light},
    % In pdftex, captions are roman by default and need to be redefined to be the light font shape used in the rest of the Document.
    % With fontspec, this light variant however is not set by default and has no shorthand version; so we need to set the fontshape l/n manually.
    FontFace={l}{n}{*-Light},
    FontFace={l}{it}{*-LightItalic},
    BoldFont={*-Bold},
    ItalicFont={*-LightItalic},
    BoldItalicFont={*-BoldItalic},
    Scale=0.917
  ]{FrutigerLTCom}

  \setmonofont[Scale=0.917]{Fira Mono} % Used for \texttt{}
\else
  \RequirePackage[utf8]{inputenc}
  \RequirePackage{fhgfont}
  \RequirePackage{FiraMono}
  % Fix warning about wrong fontshade of euro symbol
  \DeclareFontFamily{U}{eurosym}{}
  \DeclareFontShape{U}{eurosym}{l}{n}{  <-> ssub*eurosym/m/n }{}
\fi

\setkomafont{chapter}{\fontfamily{\sfdefault}\fontseries{l}\Large\selectfont}
\setkomafont{caption}{\fontfamily{\sfdefault}\fontseries{l}\footnotesize\selectfont}
\setkomafont{section}{\fontfamily{\sfdefault}\fontseries{b}\normalsize\selectfont}
\setkomafont{subsection}{\fontfamily{\sfdefault}\fontseries{b}\normalsize\selectfont}
\setkomafont{subsubsection}{\fontfamily{\sfdefault}\fontseries{b}\normalsize\selectfont}

% FhG CD is ragged right...
%\RequirePackage[document]{ragged2e}

% Correct definition of \ifpdf:
\RequirePackage{ifpdf}
\RequirePackage{ifthen}

\newcommand{\@markpub}{\textbf{PUBLIC}}
\newcommand{\@extpub}{\detokenize{_Public}}
\newcommand{\@markrestr}{\textbf{RESTRICTED}}
\newcommand{\@extrestr}{\detokenize{_Restricted}}
\newcommand{\@markcnf}{\textbf{\color{red}CONFIDENTIAL}}
\newcommand{\@extcnf}{\detokenize{_Confidential}}
\newcommand{\@markscnf}{\textbf{\color{red}STRICTLY CONFIDENTIAL}}
\newcommand{\@extscnf}{\detokenize{_StrictlyConfidential}}
\newcommand{\@mark}{}
\edef\@fileext{}

\newif\if@mark\@markfalse
\newif\if@version\@versionfalse

\DeclareOption{public}{
	\@marktrue
    \renewcommand{\@mark}{\@markpub}
    \edef\@fileext{\@extpub}
}
\DeclareOption{restricted}{
	\@marktrue
    \renewcommand{\@mark}{\@markrestr}
    \edef\@fileext{\@extrestr}
}
\DeclareOption{internal}{
	\ClassError{aisecreport}{OA 2022/11/2B/O removed protection class "internal". You probably want to use "restricted".}
}
\DeclareOption{confidential}{
	\@marktrue
    \renewcommand{\@mark}{\@markcnf}
    \edef\@fileext{\@extcnf}
}
\DeclareOption{strictlyconfidential}{
  \@marktrue
    \renewcommand{\@mark}{\@markscnf}
    \edef\@fileext{\@extscnf}
}

\newif\if@noindent\@noindentfalse
\DeclareOption{noindent}{
	\@noindenttrue
}
\ProcessOptions\relax

\if@mark
\else
  % If we're here, no classification has been done. Refuse processing until a choice is made.
  \ClassError{aisecreport}{OA 2022/11/2B/O mandates the classification of documents. Use "restricted" as the default.}
\fi

% OA 2022/11/2B/O mandates that files have their classification appended ("cutecats.pdf" with classification "public"
% should be named "cutecats_Public.pdf"). This is a crude and rudimentary check that implements this and emits a
% \ClassWarning if not.
\IfEndWith*{\jobname}{\@fileext}{}{\ClassWarning{aisecreport}{Document classification: Your jobname should end with \@fileext}}

\if@noindent
% page layout
\RequirePackage[paper=a4paper,asymmetric,
  marginparwidth=2.7cm,
  reversemp,
  tmargin=2.6cm,
  lmargin=2.6cm,
  rmargin=2.2cm,
  bmargin=3.55cm]{geometry}
\else
\RequirePackage[paper=a4paper,asymmetric,
  marginparwidth=2.7cm,
  reversemp,
  tmargin=2.6cm,
  lmargin=5.6cm,
  rmargin=2.2cm,
  bmargin=3.55cm]{geometry}
\fi

\marginparsep3mm

\setcapindent*{0cm}

\if@noindent
\newcommand{\@secbox}[1]{\hspace{0cm}\parbox{\textwidth+3cm}{#1}}
\else
\newcommand{\@secbox}[1]{\hspace{-3cm}\parbox{\textwidth+3cm}{#1}}
\fi

% Re-define \chapterformat only if it is defined and not
% \relax without making it \relax if it is not defined:
\if@noindent
\begingroup
\expandafter\expandafter\expandafter\endgroup
\expandafter\ifx\csname chapterformat\endcsname\relax\else
\renewcommand*{\chapterformat}{%
    {\hspace{0cm}%
        % Following line is the original definition
        \chapappifchapterprefix{\ }\thechapter\autodot\enskip
    }%
}
\fi
\else
\begingroup
\expandafter\expandafter\expandafter\endgroup
\expandafter\ifx\csname chapterformat\endcsname\relax\else
\renewcommand*{\chapterformat}{%
    {\hspace{-3cm}%
        % Following line is the original definition
        \chapappifchapterprefix{\ }\thechapter\autodot\enskip
    }%
}
\fi
\fi

% % Re-define \othersectionlevelsformat
% \renewcommand*{\othersectionlevelsformat}[1]{%
%   {\hspace{-3.05cm}%
%     % Following line is the original definition
%     \csname the#1\endcsname\autodot\enskip
%   }%
% }

% \RedeclareSectionCommand does not allow to use \raggedsection to left align the section.
% Therefore, we achieve that by using a negative indentation.
\if@noindent
\else
\newlength{\negativeIndentForHeadings}
\setlength{\negativeIndentForHeadings}{-85pt}
\RedeclareSectionCommand[
  indent=\negativeIndentForHeadings,
]{section}
\RedeclareSectionCommand[
  indent=\negativeIndentForHeadings,
]{subsection}
\RedeclareSectionCommand[
  indent=\negativeIndentForHeadings,
]{subsubsection}
\fi

% header/footer
\RequirePackage{scrlayer-scrpage}
\clearpairofpagestyles

\setlength{\footheight}{35pt}
\setlength{\footskip}{65pt}

\newcommand*{\@pagenumbersep}{\,|\,}

\def\rightfooter{{\parbox[t]{6cm}{%
    \normalfont\upshape\tiny\flushright
    Fraunhofer AISEC
    \if@mark
        \ ---\ \@mark
    \fi
    \\\@title
    \if@version
      \\{Version\,\@version}
    \fi
    }%
  \parbox[t]{1.5cm}{%
    \normalfont\flushright\pagemark{}\@pagenumbersep\pageref{LastPage}}}}

\if@noindent
\def\leftfooter{\hspace{0cm}\parbox[t]{1.5cm}{%
    \normalfont\flushleft\pagemark{}\@pagenumbersep\pageref{LastPage}}%
  \parbox[t]{6cm}{%
	\normalfont\upshape\tiny\flushleft
	Fraunhofer AISEC
    \if@mark
        \ ---\ \@mark
    \fi
    \\\@title
    \if@version
      \\{Version\,\@version}
    \fi
    }}%
\else
\def\leftfooter{\hspace{-3cm}\parbox[t]{1.5cm}{%
    \normalfont\flushleft\pagemark{}\@pagenumbersep\pageref{LastPage}}%
  \parbox[t]{6cm}{%
    \normalfont\upshape\tiny\flushleft
    Fraunhofer AISEC
    \if@mark
        \ ---\ \@mark
    \fi
    \\\@title
    \if@version
      \\{Version\,\@version}
    \fi
    }}%
\fi

\rofoot[\rightfooter]{\rightfooter}
\lefoot[\leftfooter]{\leftfooter}

\rohead[]{\normalfont\upshape\footnotesize\headmark}
\if@noindent
\lehead[]{\hspace{0cm}\normalfont\upshape\footnotesize\headmark}
\else
\lehead[]{\hspace{-3cm}\normalfont\upshape\footnotesize\headmark}
\fi

\automark[section]{chapter}
\pagestyle{scrheadings}

% margin notes
\let\oldmargin\marginpar
\newcommand\myMargin[1]{\oldmargin{\RaggedRight
    \fontfamily{\sfdefault}\fontseries{l}\footnotesize\selectfont\hspace{0pt}#1}}
\renewcommand{\marginpar}[1]{\myMargin{#1}}


% latest version of koma-script defines \subtitle itself
\ifx\subtitle \@undefined
  \newcommand*{\@subtitle}{}
  \newcommand{\subtitle}[1]{\gdef\@subtitle{#1}}
\fi

\ifx\keywords \@undefined
  \newcommand*{\@keywords}{}
  \newcommand{\keywords}[1]{\gdef\@keywords{#1}}
\fi

\ifx\version \@undefined
  \newcommand*{\@version}{}
  \newcommand{\version}[1]{\@versiontrue\gdef\@version{#1}}
\fi



% modified definition of \maketitle taken from scrreprt.cls:
\RequirePackage{graphicx} % we need this for the logo

\renewcommand*\maketitle[1][1]{%
  \hypersetup{%
    pdftitle={\@title},
    pdfsubject={\@subtitle},
    pdfauthor={\@author},
    pdfmoddate={\@date},
    pdfkeywords={\@keywords}
  }
    \begin{titlepage}%
    \setcounter{page}{#1}
    \let\footnotesize\small
    \let\footnoterule\relax
    \let\footnote\thanks
    \renewcommand*\thefootnote{\@fnsymbol\c@footnote}%
    \let\@oldmakefnmark\@makefnmark
    \renewcommand*{\@makefnmark}{\rlap\@oldmakefnmark}
    \hfill\includegraphics[width=60mm]{aisec_logo}
    \ifx\@extratitle\@empty \else
        \noindent\@extratitle\next@tpage\cleardoublepage
        \thispagestyle{empty}
    \fi
    \ifx\@titlehead\@empty \else
        \noindent\begin{minipage}[t]{\textwidth}
        \@titlehead
        \end{minipage}\par
    \fi
    \null\vfill
    %\begin{center}
    \ifx\@subject\@empty \else
        {\Large \@subject \par}
        \vskip 3em
    \fi
    {\titlefont\huge\raggedright \@title\par}
    \ifx\@subtitble\@empty \else
        {{\huge\raggedright \@subtitle\par}}
    \fi
    \if@mark
        \vskip 1.5em
        {\huge\@mark\par}
    \fi
    \vskip 3em
    {\Large \lineskip 0.75em \@author\par}
    \vskip 1.5em
    {\Large \@date \par}
    \vskip \z@ \@plus3fill
    {\Large \@publishers \par}
    \vskip 3em
    %\end{center}\par
    \@thanks
    \vfill\null
    \if@twoside\next@tpage
        \noindent\begin{minipage}[t]{\textwidth}
        \@uppertitleback
        \if@version
          \ifx\@uppertitleback\@empty \else
            \ ---\ %
          \fi
          {Version\,\@version}
        \fi
        \if@mark
          \if@version
            \ ---\ %
          \else
            \ifx\@uppertitleback\@empty \else
              \ ---\ %
            \fi
          \fi
          \@mark
        \fi
        \end{minipage}\par
        \vfill
        \noindent\begin{minipage}[b]{\textwidth}
        \@lowertitleback
        \end{minipage}
    \fi
    \ifx\@dedication\@empty \else
        \next@tpage\null\vfill
        {\centering \Large \@dedication \par}
        \vskip \z@ \@plus3fill
        \if@twoside \next@tpage\cleardoublepage \fi
    \fi
    \end{titlepage}
    \setcounter{footnote}{0}%
    \global\let\thanks\relax
    \global\let\maketitle\relax
    \global\let\@thanks\@empty
    \global\let\@author\@empty
    \global\let\@date\@empty
    %\global\let\@title\@empty
    \global\let\@extratitle\@empty
    \global\let\@titlehead\@empty
    \global\let\@subject\@empty
    \global\let\@publishers\@empty
    \global\let\@uppertitleback\@empty
    \global\let\@lowertitleback\@empty
    \global\let\@dedication\@empty
    \global\let\author\relax
    \global\let\title\relax
    \global\let\extratitle\relax
    \global\let\titlehead\relax
    \global\let\subject\relax
    \global\let\publishers\relax
    \global\let\uppertitleback\relax
    \global\let\lowertitleback\relax
    \global\let\dedication\relax
    \global\let\date\relax
    \global\let\and\relax}



% some useful stuff that we do not need here, but that we want to load
% by default to keep the preamble short
\RequirePackage[%pdftex,            % make links clickable
  pdfauthor={Fraunhofer AISEC},
  colorlinks=true,
  linkcolor=black, citecolor=black, urlcolor=black,
  pdfhighlight=/P,
  pagebackref=false,
  bookmarksnumbered=true,  % Nummerierung der Bookmarks
  bookmarkstype=toc,       % Art der Verzeichnisses
  % Anchors
  plainpages=false,        % Anchors even on plain pages ?
  pageanchor=true,         % Pages are linkable
  % PDF Informationen
  pdfcreator={LaTeX, hyperref, KOMA-Script}, % Ersteller
  pdfstartview=FitH,       % Dokument wird Fit Width geaefnet
  pdfpagemode=UseOutlines, % Bookmarks im Viewer anzeigen
  pdfpagelabels=true,      % set PDF page labels
  bookmarksopenlevel=3]{hyperref} % must be loaded in between nameref/varioref and babel!

\RequirePackage{url}               % provide \url{} to typeset URLs nicely
\def\UrlFont{\fontfamily{\sfdefault}\fontseries{m}\fontshape{n}\normalsize\selectfont}

\RequirePackage{booktabs,tabulary} % typeset nice tables
\RequirePackage{calc}

\ifpdf
% Optischer Randausgleich mit pdfTeX
\usepackage[%
        expansion=true, % better typography, but with much larger PDF file.
        protrusion=true
]{microtype}
\fi





%
% nonpublic environment
%
% include non-public part within this environment.
% use \includenonpublic at begin of the document to show these parrs.
% Otherwise parts will be excluded.


% treat stuff inside nonpublic environment as verbatim and drop it
\RequirePackage{verbatim,xcolor}

\definecolor{public}{rgb}{0.1, 0.6, 0.0}
\definecolor{nonpublic}{rgb}{0.0, 0.1, 0.8}


\makeatletter
\def\nonpublic{\@bsphack
             \let\do\@makeother\dospecials\catcode`\^^M\active
             \let\verbatim@startline\relax
             \let\verbatim@addtoline\@gobble
             \let\verbatim@processline\relax
             \let\verbatim@finish\relax
             \verbatim@}
\let\endnonpublic=\@esphack

\newenvironment{public}{\color{public}}{}

% in order to include, redifne as environment that does nothing:
\def\includenonpublic{\renewenvironment{nonpublic}{\color{nonpublic}}{}
\def\public{\@bsphack
             \let\do\@makeother\dospecials\catcode`\^^M\active
             \let\verbatim@startline\relax
             \let\verbatim@addtoline\@gobble
             \let\verbatim@processline\relax
             \let\verbatim@finish\relax
             \verbatim@}
\let\endnonpublic=\@esphack}

\makeatother

\newcommand{\comm}[1]{{\color{red}#1}}
\def\nocomments{\renewcommand{\comm}[1]{}}


\newcommand{\mymultirow}[1]{%
  \begin{picture}(0,0)%
    \put(0,0){%
      \parbox[t]{\hsize}{#1}%
    }%
  \end{picture}%
}%


%
% code taken and adapted from mcaption.sty
%

\RequirePackage{chngpage}

\cpoddpagefalse

\makeatletter

\newcommand*{\margincapalign}{t}
\newlength{\margincapsep}
\AtBeginDocument{%
  \setlength{\margincapsep}{\marginparsep}%
}
\newsavebox{\mcaption@ObjectBox}
\newsavebox{\mcaption@CaptionBox}
\newlength{\mcaption@ObjectHeight}
\newlength{\mcaption@ObjectRaise}
\newlength{\mcaption@CaptionRaise}
\newlength{\mcaption@tempdima}

\newenvironment{margincap}[2][\mcaption@DefaultOpt]{%
  \def\mcaption@DefaultOpt{#2}%
  \begin{lrbox}{\mcaption@CaptionBox}%
    \setlength{\mcaption@tempdima}{\marginparsep}%
    \addtolength{\mcaption@tempdima}{\marginparwidth}%
    \addtolength{\mcaption@tempdima}{-\margincapsep}%
    \begin{minipage}[\margincapalign]{\mcaption@tempdima}%
       \caption[#1]{#2}%
    \end{minipage}%
  \end{lrbox}%
  \begin{lrbox}{\mcaption@ObjectBox}%
    \begin{minipage}[\margincapalign]{\linewidth}%
}{%
    \end{minipage}%
  \end{lrbox}%
  \settoheight{\mcaption@ObjectHeight}{\usebox{\mcaption@ObjectBox}}%
  \ifthenelse{\equal{\margincapalign}{t}}{%
    \setlength{\mcaption@ObjectRaise}{-\mcaption@ObjectHeight}%
    \setlength{\mcaption@ObjectHeight}{0pt}%
    \settoheight{\mcaption@CaptionRaise}{\strut}%
  }{%
    \setlength{\mcaption@ObjectRaise}{0pt}%
    \setlength{\mcaption@CaptionRaise}{0pt}%
  }%
  \if@twoside%
    \checkoddpage%
  \else%
    \cpoddpagetrue%
  \fi%
    \makebox[\linewidth][r]{%
      \raisebox{\mcaption@CaptionRaise}[0pt][0pt]{%
        \usebox{\mcaption@CaptionBox}%
      }%
      \hspace*{\margincapsep}%
      \raisebox{\mcaption@ObjectRaise}[\mcaption@ObjectHeight]{%
        \usebox{\mcaption@ObjectBox}%
      }%
    }%
}%


% *-version without figure number
\newenvironment{margincap*}[2][\mcaption@DefaultOpt]{%
  \def\mcaption@DefaultOpt{#2}%
  \begin{lrbox}{\mcaption@CaptionBox}%
    \setlength{\mcaption@tempdima}{\marginparsep}%
    \addtolength{\mcaption@tempdima}{\marginparwidth}%
    \addtolength{\mcaption@tempdima}{-\margincapsep}%
    \begin{minipage}[\margincapalign]{\mcaption@tempdima}%
      \vskip\abovecaptionskip\usekomafont{caption}#2%
    \end{minipage}%
  \end{lrbox}%
  \begin{lrbox}{\mcaption@ObjectBox}%
    \begin{minipage}[\margincapalign]{\linewidth}%
}{%
    \end{minipage}%
  \end{lrbox}%
  \settoheight{\mcaption@ObjectHeight}{\usebox{\mcaption@ObjectBox}}%
  \ifthenelse{\equal{\margincapalign}{t}}{%
    \setlength{\mcaption@ObjectRaise}{-\mcaption@ObjectHeight}%
    \setlength{\mcaption@ObjectHeight}{0pt}%
    \settoheight{\mcaption@CaptionRaise}{\strut}%
  }{%
    \setlength{\mcaption@ObjectRaise}{0pt}%
    \setlength{\mcaption@CaptionRaise}{0pt}%
  }%
  \if@twoside%
    \checkoddpage%
  \else%
    \cpoddpagetrue%
  \fi%
    \makebox[\linewidth][r]{%
      \raisebox{\mcaption@CaptionRaise}[0pt][0pt]{%
        \usebox{\mcaption@CaptionBox}%
      }%
      \hspace*{\margincapsep}%
      \raisebox{\mcaption@ObjectRaise}[\mcaption@ObjectHeight]{%
        \usebox{\mcaption@ObjectBox}%
      }%
    }%
}%


% Macro for wide figures/tables including left margin

\newlength{\widefigurewidth}
\setlength\widefigurewidth{\textwidth+\marginparwidth+\marginparsep}


\newenvironment{widecap}[2][\mcaption@DefaultOpt]{%
  \def\mcaption@DefaultOpt{#2}%
  \setcapwidth[l]{\widefigurewidth}
  \begin{lrbox}{\mcaption@CaptionBox}%
    \begin{minipage}[b]{\widefigurewidth}%
      \caption[#1]{#2}%
    \end{minipage}%
  \end{lrbox}%
  \begin{lrbox}{\mcaption@ObjectBox}%
    \begin{minipage}[b]{\widefigurewidth}%
}{%
  \end{minipage}%
  \end{lrbox}%
  \makebox[\textwidth][r]{%
    \usebox{\mcaption@ObjectBox}}
  \makebox[\textwidth][r]{
    \usebox{\mcaption@CaptionBox}}
}

% *-version without figure number
\newenvironment{widecap*}[2][\mcaption@DefaultOpt]{%
  \def\mcaption@DefaultOpt{#2}%
  \setcapwidth[l]{\widefigurewidth}
  \begin{lrbox}{\mcaption@CaptionBox}%
    \begin{minipage}[b]{\widefigurewidth}%
      \vskip\abovecaptionskip\usekomafont{caption}#2%
    \end{minipage}%
  \end{lrbox}%
  \begin{lrbox}{\mcaption@ObjectBox}%
    \begin{minipage}[b]{\widefigurewidth}%
}{%
  \end{minipage}%
  \end{lrbox}%
  \makebox[\textwidth][r]{%
    \usebox{\mcaption@ObjectBox}}
  \makebox[\textwidth][r]{
    \usebox{\mcaption@CaptionBox}}
}



% sideways figures
% \RequirePackage{rotating}

% \newlength{\sidewaysfigurewidth}
% \setlength\sidewaysfigurewidth{\textheight}


% \newenvironment{sidewayscap}[2][\mcaption@DefaultOpt]{%
%   \def\mcaption@DefaultOpt{#2}%
%   \setcapwidth[l]{\sidewaysfigurewidth}
%   \begin{lrbox}{\mcaption@CaptionBox}%
%     \begin{minipage}[b]{\sidewaysfigurewidth}%
%       \caption[#1]{#2}%
%     \end{minipage}%
%   \end{lrbox}%
%   \begin{lrbox}{\mcaption@ObjectBox}%
%     \begin{minipage}[b]{\sidewaysfigurewidth}%
% }{%
%   \end{minipage}%
%   \end{lrbox}%
%   \makebox[\linewidth][r]{%
%     \begin{sideways}
%     \raisebox{\textwidth}{\usebox{\mcaption@ObjectBox}}
%     \par
%     \usebox{\mcaption@CaptionBox}
%   \end{sideways}
% }%
% }



\makeatother

% vim: textwidth=72 filetype=tex nofoldenable:
