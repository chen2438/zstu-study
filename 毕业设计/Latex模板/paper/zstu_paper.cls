\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{zstu_paper}[2024/02/06 Zhejiang Sci-Tech University Paper Class]

\AddToHook{package/xeCJK/after}{\defaultCJKfontfeatures{}}
\PassOptionsToPackage{AutoFakeBold}{xeCJK}
\LoadClass[UTF8,a4paper,twoside]{ctexart}

\RequirePackage[subfigure]{tocloft}
\RequirePackage{amsmath,amssymb,amsfonts,geometry,makeidx,graphicx,caption,verbatim,pdfpages,fancyhdr,placeins,xcolor,enumitem,subfigure,float,chngcntr,setspace,etoolbox}
\RequirePackage{txfonts}
\RequirePackage[colorlinks=true,allcolors=black]{hyperref}
\RequirePackage[nameinlink]{cleveref}
\RequirePackage[linesnumbered,ruled,vlined]{algorithm2e}
% \RequirePackage[backend=biber,style=gb7714-2015,gbnoauthor=true,gbnamefmt=lowercase]{biblatex}
\RequirePackage[backend=biber,style=gb7714-2015,gbnoauthor=true,gbnamefmt=lowercase,gbpunctin=false]{biblatex}
\DeclareFieldFormat[inproceedings]{booktitle}{#1[C]}
\DefineBibliographyStrings{english}{in={In:\ }}
\makeindex

\setCJKfamilyfont{tnr_}[Path=fonts/,ItalicFont={timesi.ttf},BoldItalicFont={timesbi.ttf},BoldFont={timesbd.ttf}]{times.ttf}
\setCJKfamilyfont{st_}[Path=fonts/,AutoFakeBold,AutoFakeSlant]{AdobeSongStd.otf}
\setCJKfamilyfont{fs_}[Path=fonts/,AutoFakeBold,AutoFakeSlant]{AdobeFangsongStd.otf}
\setCJKfamilyfont{sh}[Path=fonts/,BoldFont={AdobeHeitiStd.otf}]{AdobeSongStd.otf}
\setCJKmainfont[Path=fonts/,AutoFakeBold,AutoFakeSlant]{AdobeSongStd.otf}
% \setmainfont[Path=fonts,ItalicFont={timesi.ttf},BoldItalicFont={timesbi.ttf},BoldFont={timesbd.ttf}]{times.ttf}
\setCJKfamilyfont{ht_}[Path=fonts/,AutoFakeBold,AutoFakeSlant]{AdobeHeitiStd.otf}
\setCJKfamilyfont{kt_}[Path=fonts/,AutoFakeBold,AutoFakeSlant]{AdobeKaitiStd.otf}

% 设置页边距
\geometry{left=3.18cm,right=3.18cm,top=2.54cm,bottom=2.54cm}
\setlength{\headheight}{12.7pt}

% 1.5 * 1.3 / 1.2
% https://blog.csdn.net/weixinhum/article/details/104594454
\linespread{1.625}
\zihao{-4}
\ctexset{
	section={
		name={第,章},
		number=\arabic{section},
		format=\raggedright\heiti\zihao{3},
		beforeskip=0ex,
		afterskip=0.5ex,
		aftername=\enspace,
	},
	subsection={
		format=\raggedright\heiti\zihao{4},
		beforeskip=0.5ex,
		afterskip=0ex,
		aftername=\enspace,
	},
	subsubsection={
		format=\raggedright\heiti\zihao{-4},
		beforeskip=1ex,
		afterskip=1ex,
		aftername=\enspace,
	},
	paragraph={
		format=\CJKfamily{sh}\bfseries\zihao{-4},
		beforeskip=0ex,
		afterskip=1em,
	},
	contentsname={\hfill\textnormal{\zihao{3}\heiti\bfseries{目 \quad 录}}\hfill},
}

% 脚注样式
\renewcommand{\footnotesize}{\zihao{-5}}

% 在每章节开始时重置图表计数器
\counterwithin{figure}{section}
\counterwithin{table}{section}
\counterwithin{equation}{section}
\counterwithin{algocf}{section}
% 图表题注样式
\renewcommand{\figurename}{图}
\renewcommand{\tablename}{表}
\renewcommand{\algorithmcfname}{算法}
\crefname{figure}{图}{图}
\crefname{table}{表}{表}
\renewcommand{\thefigure}{\arabic{section}-\arabic{figure}}
\renewcommand{\thetable}{\arabic{section}-\arabic{table}}
\renewcommand{\theequation}{\arabic{section}-\arabic{equation}}
\renewcommand{\thealgocf}{\arabic{section}-\arabic{algocf}}
\DeclareCaptionFont{five}{\zihao{5}\songti\bfseries}
\captionsetup[figure]{labelsep=quad,font=five}
\captionsetup[table]{labelsep=quad,font=five,position=top}
% 算法格式
\SetAlgoCaptionSeparator{}
\SetAlCapFnt{\zihao{5}\songti}
\SetAlCapNameFnt{\quad\zihao{5}\songti\bfseries}
\setlength{\interspacetitleruled}{3pt}

% 表格样式
\newcommand{\settablefontsize}{\zihao{-5}}
\AtBeginEnvironment{tabular}{\settablefontsize}

% 定义页眉页脚
\fancypagestyle{tocstyle}{
	\fancyhf{} % clear all header and footer fields
	\renewcommand{\headrulewidth}{0pt}
	\fancyfoot[C]{\zihao{-5}\thepage}
}
\fancypagestyle{mainstyle}{
	\fancyhf{}
	\renewcommand{\headrulewidth}{0.3pt}
	\fancyhead[CO]{\zihao{5}\fangsong{浙江理工大学本科毕业设计（论文）}}
	\fancyhead[CE]{\zihao{5}\fangsong{\@title}}
	\fancyfoot[C]{\zihao{-5}\thepage}
}

% 设置目录样式
\setlength\cftbeforetoctitleskip{0ex}
\setlength\cftaftertoctitleskip{0ex}
\setlength\cftbeforesecskip{0ex}
\setlength\cftbeforepartskip{0ex}
\renewcommand{\cftpartfont}{\zihao{-4}\heiti}
\renewcommand{\cftsecfont}{\zihao{-4}\heiti}
\renewcommand{\cftsubsecfont}{\zihao{5}\songti}
\renewcommand{\cftsubsubsecfont}{\zihao{5}\fangsong}
\renewcommand{\cftsecpagefont}{\mdseries}
\renewcommand{\cftdotsep}{1} % 设置点的密集程度，默认4.5
\renewcommand{\cftsecleader}{\cftdotfill{\cftdotsep}}

% 摘要无页码
\pagestyle{empty}

% 参考文献样式
\defbibheading{MyBibHeadingStyle}{
	\phantomsection
	\pdfbookmark[1]{参考文献}{bookmark:参考文献}
	\cftaddtitleline{toc}{section}{参考文献}{\thepage}
	\begin{center}
		\heiti \zihao{4}{参考文献}
	\end{center}
}
\addbibresource[location=local]{reference.bib}

% 制作目录
\newcommand{\maketoc}{
	\pdfbookmark[1]{目录}{bookmark:目录}
	\pagestyle{tocstyle}
	\fancypagestyle{plain}{
		\pagestyle{tocstyle}
	}
	\pagenumbering{Roman}
	\tableofcontents

	\newpage
	\pagestyle{mainstyle}
	\fancypagestyle{plain}{
		\pagestyle{mainstyle}
	}
	\pagenumbering{arabic}
}

% 插入参考文献
\newcommand{\makereference}{\printbibliography[heading=MyBibHeadingStyle]}

% 中文摘要
\newcommand{\abstractzh}[2]{
	\phantomsection
	\pdfbookmark[1]{摘要}{bookmark:摘要}
	\cftaddtitleline{toc}{part}{摘 \quad 要}{}
	\begin{center}\heiti\zihao{-3}摘 \quad 要\end{center}
	\zihao{-4}

	#1

	\vspace{1ex}\noindent\heiti{关键词：}\songti#2
	\newpage
}

% 英文摘要
\newcommand{\abstracten}[2]{
	\phantomsection
	\pdfbookmark[1]{Abstract}{bookmark:Abstract}
	\cftaddtitleline{toc}{part}{Abstract}{}
	\begin{center}\bfseries\zihao{-3}Abstract\end{center}
	\zihao{-4}

	#1

	\vspace{1ex}\noindent\textbf{Keywords: }#2
	\newpage
}

% 致谢
\newenvironment{acknowledgement}{
	\phantomsection
	\pdfbookmark[1]{致谢}{bookmark:致谢}
	\begin{center}\heiti\zihao{3}致 \quad 谢\end{center}
	\cftaddtitleline{toc}{section}{致 \quad 谢}{\thepage}

	\indent
}{
	\newpage
}

% 设置有序/无序列表段落间距
\setenumerate[1]{itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
\setitemize[1]{itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
\setdescription{itemsep=0pt,partopsep=0pt,parsep=\parskip,topsep=5pt}
