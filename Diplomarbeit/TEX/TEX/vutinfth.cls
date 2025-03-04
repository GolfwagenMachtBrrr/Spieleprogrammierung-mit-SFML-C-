%%
%% This is file `vutinfth.cls',
%% generated with the docstrip utility.
%%
%% The original source files were:
%%
%% vutinfth.dtx  (with options: `class')
%% 
%% This is a generated file.
%% Copyright (C) 2014-2023 by Thomas Auzinger <thomas@auzinger.name>
%% 
%% This work may be distributed and/or modified under the
%% conditions of the LaTeX Project Public License, either version 1.3
%% The latest version of this license is in
%%   http://www.latex-project.org/lppl.txt
%% and version 1.3 or later is part of all distributions of LaTeX
%% version 2005/12/01 or later.
%% 
%% This work has the LPPL maintenance status `maintained'.
%% 
%% The Current Maintainer of this work is Thomas Auzinger.
%% 
%% This work consists of the files vutinfth.dtx and vutinfth.ins
%% and the derived file vutinfth.cls.
%% This work also consists of the file intro.tex.
%% 
%% vutinfth.dtx
%% Copyright (C) 2014-2023 by Thomas Auzinger <thomas@auzinger.name>
\NeedsTeXFormat{LaTeX2e}[1999/12/01]
\ProvidesClass{vutinfth}
[2023/06/04 v1.12 TU Wien Informatics thesis template]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\DeclareOption*{%
	\PassOptionsToClass{\CurrentOption}{memoir}%
}%
\ProcessOptions\relax
\LoadClass[a4paper,11pt]{memoir}%
\chapterstyle{veelo}%
\RequirePackage[scaled]{helvet}%
\RequirePackage{lmodern}%
\RequirePackage{courier}%
\RequirePackage[T1]{fontenc}%
\RequirePackage[english,naustrian]{babel}%
\RequirePackage[useregional]{datetime2}%
\RequirePackage{geometry}%
\RequirePackage{calc}%
\RequirePackage{etoolbox}%
\RequirePackage{graphicx}%
\graphicspath{{graphics/}}%
\newcommand{\@namexdef}[1]{\expandafter\xdef\csname#1\endcsname}%
\newcommand{\ifestrequal}[4]{%
	\begingroup
	\edef\vutinfth@tempa{{#1}}%
	\edef\vutinfth@tempb{{#2}}%
	\expandafter\expandafter\expandafter\ifstrequal
	\expandafter\vutinfth@tempa\vutinfth@tempb{#3}{#4}%
	\endgroup
}%
\newcommand{\vutinfth@HUGE}{\fontsize{30}{34}\selectfont}%
\newcommand{\vutinfth@huge}{\fontsize{20}{23}\selectfont}%
\newcommand{\vutinfth@LARGE}{\fontsize{17}{22}\selectfont}%
\newcommand{\vutinfth@Large}{\fontsize{14}{18}\selectfont}%
\newcommand{\vutinfth@large}{\fontsize{12}{14.5}\selectfont}%
\newcommand{\vutinfth@normalsize}{\fontsize{11}{13.6}\selectfont}%
\newenvironment{SFFont}[1]{%
	\begingroup
	\sffamily
	\global\let\vutinfth@f@family@tmp=\f@family
	\endgroup
	\renewcommand{\sfdefault}{#1}%
	\ifdefstrequal{\f@family}{\vutinfth@f@family@tmp}{\sffamily}{}%
}{%
	\renewcommand{\sfdefault}{\vutinfth@f@family@tmp}%
}%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\newcommand{\setdate}[3]{%
	\DTMsavedate{vutinfth@date@signing}{#3-#2-#1}%
}%
\newcommand{\vutinfth@def@data}[2]{%
	\@namedef{vutinfth@data@#1@def}{}%
	\@namedef{vutinfth@data@#1}{#2}%
}%
\newcommand{\vutinfth@def@data@invalid}[2]{%
	\@namedef{vutinfth@data@#1@error}{%
		\ClassError{vutinfth}{No #2 issued}{Set #1 with #2.}%
	}%
	\@namedef{vutinfth@data@#1}{\@nameuse{vutinfth@data@#1@error}}%
}%
\newcommand{\CreateData}[1]{%
	\@namedef{set#1}##1{%
		\vutinfth@def@data{#1}{##1}%
	}%
	\vutinfth@def@data@invalid{#1}{\string\set#1}%
}%
\newcommand{\vutinfth@person@male}{male}%
\newcommand{\vutinfth@person@female}{female}%
\newcommand{\ifmale}[2]{%
	\ifcsstring{vutinfth@person@#1@gender}{\vutinfth@person@male}{#2}{}%
}%
\newcommand{\iffemale}[2]{%
	\ifcsstring{vutinfth@person@#1@gender}{\vutinfth@person@female}{#2}{}%
}%
\newcommand{\vutinfth@def@person}[5]{%
	\@namedef{vutinfth@person@#1@def}{}%
	\@namedef{vutinfth@person@#1@pretitle}{#2}%
	\@namedef{vutinfth@person@#1@name}{#3}%
	\@namedef{vutinfth@person@#1@posttitle}{#4}%
	\ifdefstring{\vutinfth@person@male}{#5}{%
		\@namedef{vutinfth@person@#1@gender}{\vutinfth@person@male}%
	}{}%
	\ifdefstring{\vutinfth@person@female}{#5}{%
		\@namedef{vutinfth@person@#1@gender}{\vutinfth@person@female}%
	}{}%
	\ifstrempty{#3}{%
		\ifstrempty{#2}{%
			\@namedef{vutinfth@person@#1@fullname}{#4}%
		}{%
			\ifstrempty{#4}{%
				\@namedef{vutinfth@person@#1@fullname}{#2}%
			}{%
				\@namedef{vutinfth@person@#1@fullname}{#2 #4}%
			}%
		}%
	}{%
		\ifstrempty{#2}{%
			\ifstrempty{#4}{%
				\@namedef{vutinfth@person@#1@fullname}{#3}%
			}{%
				\@namedef{vutinfth@person@#1@fullname}{#3, #4}%
			}%
		}{%
			\ifstrempty{#4}{%
				\@namedef{vutinfth@person@#1@fullname}{#2 #3}%
			}{%
				\@namedef{vutinfth@person@#1@fullname}{#2 #3, #4}%
			}%
		}%
	}%
}%
\newcommand{\vutinfth@def@person@invalid}[2]{%
	\@namedef{vutinfth@person@#1@error}{%
		\ClassError{vutinfth}{No #2 issued}{Set #1 with #2.}%
	}%
	\@namedef{vutinfth@person@#1@name}{%
		\@nameuse{vutinfth@person@#1@error}}%
	\@namedef{vutinfth@person@#1@pretitle}{%
		\@nameuse{vutinfth@person@#1@error}}%
	\@namedef{vutinfth@person@#1@posttitle}{%
		\@nameuse{vutinfth@person@#1@error}}%
	\@namedef{vutinfth@person@#1@gender}{%
		\@nameuse{vutinfth@person@#1@error}}%
	\@namedef{vutinfth@person@#1@fullname}{%
		\@nameuse{vutinfth@person@#1@error}}%
}%
\newcommand{\CreatePerson}[1]{%
	\@namedef{set#1}##1##2##3##4{%
		\vutinfth@def@person{#1}{##1}{##2}{##3}{##4}%
	}%
	\vutinfth@def@person@invalid{#1}{\string\set#1}%
}%
\newcommand{\AddLanguage}[1]{%
	\@namedef{KV@vutinfth@#1}##1{%
		\@namedef{vutinfth@current@#1}{##1}%
	}%
	\@nameuse{KV@vutinfth@#1}{}%
	\ifundef{\vutinfth@allocate@polylingual}{%
		\newcommand{\vutinfth@allocate@polylingual}[1]{\@empty}%
	}{}%
	\@namelet{vutinfth@allocate@polylingual@#1}%
	\vutinfth@allocate@polylingual
	\renewcommand{\vutinfth@allocate@polylingual}[1]{%
		\@nameuse{vutinfth@allocate@polylingual@#1}{##1}%
		\@namexdef{vutinfth@##1@#1}{%
			\ifcsempty{vutinfth@current@#1}{%
				\ifdraftdoc{%
					[Draft: No `#1' text for polylingual `##1'.]%
				}\else{%
					\relax
				}\fi
			}{%
				\@nameuse{vutinfth@current@#1}%
			}%
		}%
	}%
	\ifundef{\vutinfth@selectlanguage@polylingual}{%
		\newcommand{\vutinfth@selectlanguage@polylingual}[1]{\@empty}%
	}{}%
	\@namelet{vutinfth@selectlanguage@polylingual@#1}%
	\vutinfth@selectlanguage@polylingual
	\renewcommand{\vutinfth@selectlanguage@polylingual}[1]{%
		\@nameuse{vutinfth@selectlanguage@polylingual@#1}{##1}%
		\ifdefstring{\languagename}{#1}{\@nameuse{vutinfth@##1@#1}}{}%
	}%
}%
\newcommand{\CreatePolylingual}[2][]{%
	\begingroup
	\setkeys{vutinfth}{#1}%
	\vutinfth@allocate@polylingual{#2}%
	\endgroup
	\@namedef{vutinfth@polylingual@#2}{%
		\vutinfth@selectlanguage@polylingual{#2}}%
}%
\newcommand{\vutinfth@thesis@basetype@undergraduate}{%
	vutinfth@undergraduate}%
\newcommand{\vutinfth@thesis@basetype@graduate}{%
	vutinfth@graduate}%
\newcommand{\ifundergraduate}[1]{%
	\ifestrequal{\vutinfth@thesis@basetype}{%
		\vutinfth@thesis@basetype@undergraduate
	}{#1}{}%
}%
\newcommand{\ifgraduate}[1]{%
	\ifestrequal{\vutinfth@thesis@basetype}{%
		\vutinfth@thesis@basetype@graduate
	}{#1}{}%
}%
\newcommand{\vutinfth@thesis@basetype}{%
	\ClassError{vutinfth}{No \string\setthesis \space issued}{%
		Set thesis type with \string\setthesis.}%
}%
\newcommand{\vutinfth@polylingual@degreename}{%
	\ClassError{vutinfth}{No \string\setthesis \space issued}{%
		Set thesis type with \string\setthesis.}%
}%
\newcommand{\vutinfth@polylingual@thesisname}{%
	\ClassError{vutinfth}{No \string\setthesis \space issued}{%
		Set thesis type with \string\setthesis.}%
}%
\newcommand{\vutinfth@thesis@bachelor}{bachelor}%
\newcommand{\vutinfth@thesis@master}{master}%
\newcommand{\vutinfth@thesis@doctor}{doctor}%
\newcommand{\@setthesisname}[1]{%
	\renewcommand{\vutinfth@polylingual@thesisname}{#1}}%
\newcommand{\@setdegreename}[1]{%
	\renewcommand{\vutinfth@polylingual@degreename}{#1}}%
\newcommand{\@setgendereddegreename}[2]{%
	\ifmale{author}{\@setdegreename{#1}}%
	\iffemale{author}{\@setdegreename{#2}}%
}%
\newcommand{\setthesis}[1]{%
	\ifdefstring{\vutinfth@thesis@bachelor}{#1}{%
		\renewcommand{\vutinfth@thesis@basetype}{%
			\vutinfth@thesis@basetype@undergraduate}%
		\@setthesisname{\vutinfth@polylingual@BACHELORTHESIS}%
		\@setdegreename{\vutinfth@polylingual@Bdeg}%
	}{}%
	\ifdefstring{\vutinfth@thesis@master}{#1}{%
		\renewcommand{\vutinfth@thesis@basetype}{%
			\vutinfth@thesis@basetype@undergraduate}%
		\@setthesisname{%
			\ClassError{vutinfth}{No \string\setmasterdegree \space issued}{%
				Set masterdegree with \string\setmasterdegree.}%
		}%
		\@setdegreename{%
			\ClassError{vutinfth}{No \string\setmasterdegree \space issued}{%
				Set master degree with \string\setmasterdegree.}%
		}%
	}{}%
	\ifdefstring{\vutinfth@thesis@doctor}{#1}{%
		\renewcommand{\vutinfth@thesis@basetype}{%
			\vutinfth@thesis@basetype@graduate}%
		\@setthesisname{\vutinfth@polylingual@DOCTORTHESIS}%
		\@setdegreename{%
			\ClassError{vutinfth}{No \string\setdoctordegree \space issued}{%
				Set doctor degree with \string\setdoctordegree.}%
		}%
	}{}%
}%

\CreateData{regnumber}%
\CreateData{firstreviewerdata}%
\CreateData{secondreviewerdata}%
\CreatePerson{author}%
\CreatePerson{advisor}%
\CreatePerson{secondadvisor}%
\CreatePerson{firstassistant}%
\CreatePerson{secondassistant}%
\CreatePerson{thirdassistant}%
\CreatePerson{firstreviewer}%
\CreatePerson{secondreviewer}%
\AddLanguage{english}%
\AddLanguage{naustrian}%
\CreatePolylingual[
english=Advisor,
naustrian=Betreuung]{Advisor}%
\CreatePolylingual[
english=Second advisor,
naustrian=Zweitbetreuung]{Secondadvisor}%
\CreatePolylingual[
english=submitted in partial fulfillment of the requirements
for the degree of,
naustrian=zur Erlangung des akademischen Grades]{submission}%
\CreatePolylingual[
english=in,
naustrian=im Rahmen des Studiums]{in}%
\CreatePolylingual[
english=by,
naustrian=eingereicht von]{by}%
\CreatePolylingual[
english=Registration Number,
naustrian=Matrikelnummer]{Registrationnumber}%
\CreatePolylingual[
english=to the Faculty of Informatics,
naustrian=an der Fakult\"at f\"ur Informatik]{faculty}%
\CreatePolylingual[
english=at the TU Wien,
naustrian=der Technischen Universit\"at Wien]{university}%
\CreatePolylingual[
english=Assistance,
naustrian=Mitwirkung]{Assistance}%
\CreatePolylingual[
english=The dissertation has been reviewed by:,
naustrian=Diese Dissertation haben begutachtet:]{Reviewed}%
\CreatePolylingual[
english=External reviewers:]{Reviewers}%
\CreatePolylingual[
english=Vienna,
naustrian=Wien]{Place}%
\CreatePolylingual[
english=Declaration of Authorship,
naustrian=Erkl\"arung zur Verfassung der Arbeit]{StatementChapter}%
\CreatePolylingual[
english={I hereby declare that I have written this Doctoral Thesis
	independently, that I have completely specified the utilized
	sources and resources and that I have definitely marked all parts
	of the work - including tables, maps and figures - which belong
	to other works or to the internet, literally or extracted, by
	referencing the source as borrowed.},
naustrian={Hiermit erkl\"are ich, dass ich diese Arbeit
	selbst\"andig verfasst habe, dass ich die verwendeten Quellen
	und Hilfsmittel vollst\"andig angegeben habe und dass ich die
	Stellen der Arbeit -- einschlie{\ss}lich Tabellen, Karten und
	Abbildungen --, die anderen Werken oder dem Internet im Wortlaut
	oder dem Sinn nach entnommen sind, auf jeden Fall unter Angabe
	der Quelle als Entlehnung kenntlich gemacht habe.}]{Statement}%
\CreatePolylingual[
english=Bachelor of Science,
naustrian=Bachelor of Science]{Bdeg}%
\CreatePolylingual[
english=Master of Science,
naustrian=Master of Science]{MdegMaster}%
\CreatePolylingual[
english=Diplom-Ingenieur,
naustrian=Diplom-Ingenieur]{MdegDiplMale}%
\CreatePolylingual[
english=Diplom-Ingenieurin,
naustrian=Diplom-Ingenieurin]{MdegDiplFemale}%
\CreatePolylingual[
english=Magister der Naturwissenschaften,
naustrian=Magister der Naturwissenschaften]{MdegRerNatMale}%
\CreatePolylingual[
english=Magistra der Naturwissenschaften,
naustrian=Magistra der Naturwissenschaften]{MdegRerNatFemale}%
\CreatePolylingual[
english=Magister der Sozial- und Wirtschaftswissenschaften,
naustrian=Magister der Sozial- und Wirtschaftswissenschaften]{%
	MdegRerSocOecMale}%
\CreatePolylingual[
english=Magistra der Sozial- und Wirtschaftswissenschaften,
naustrian=Magistra der Sozial- und Wirtschaftswissenschaften]{%
	MdegRerSocOecFemale}%
\CreatePolylingual[
english=Doktor der Naturwissenschaften,
naustrian=Doktor der Naturwissenschaften]{DdegRerNatMale}%
\CreatePolylingual[
english=Doktorin der Naturwissenschaften,
naustrian=Doktorin der Naturwissenschaften]{DdegRerNatFemale}%
\CreatePolylingual[
english=Doktor der Technischen Wissenschaften,
naustrian=Doktor der Technischen Wissenschaften]{DdegTechnMale}%
\CreatePolylingual[
english=Doktorin der Technischen Wissenschaften,
naustrian=Doktorin der Technischen Wissenschaften]{DdegTechnFemale}%
\CreatePolylingual[
english=Doktor der Sozial- und Wirtschaftswissenschaften,
naustrian=Doktor der Sozial- und Wirtschaftswissenschaften]{%
	DdegRerSocOecMale}%
\CreatePolylingual[
english=Doktorin der Sozial- und Wirtschaftswissenschaften,
naustrian=Doktorin der Sozial- und Wirtschaftswissenschaften]{%
	DdegRerSocOecFemale}%
\CreatePolylingual[
english=BACHELOR'S THESIS,
naustrian=BACHELORARBEIT]{BACHELORTHESIS}%
\CreatePolylingual[
english=MASTER'S THESIS,
naustrian=MASTERARBEIT]{MASTERTHESIS}%
\CreatePolylingual[
english=DIPLOMA THESIS,
naustrian=DIPLOMARBEIT]{DIPLOMATHESIS}%
\CreatePolylingual[
english=DISSERTATION,
naustrian=DISSERTATION]{DOCTORTHESIS}%
\newcommand{\settitle}[2]{%
	\CreatePolylingual[english=#1,naustrian=#2]{Title}%
}%
\newcommand{\setsubtitle}[2]{%
	\CreatePolylingual[english=#1,naustrian=#2]{Subtitle}%
}%
\newcommand{\setcurriculum}[2]{%
	\CreatePolylingual[english=#1,naustrian=#2]{Curriculum}%
}%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\newcommand{\newsetlength}[2]{%
	\newlength{#1}%
	\setlength{#1}{#2}%
}%
\newcommand{\vutinfth@squarebullet}{\rule[0.47ex]{0.4ex}{0.4ex}}%
\newlength{\vutinfth@tmp@parindent}%
\newlength{\vutinfth@tmp@baselineskip}%
\newlength{\vutinfth@tmp@parskip}%
\newcommand{\vutinfth@savelayout}{%
	\setlength{\vutinfth@tmp@parindent}{\parindent}%
	\setlength{\vutinfth@tmp@baselineskip}{\baselineskip}%
	\setlength{\vutinfth@tmp@parskip}{\parskip}%
}%
\newcommand{\vutinfth@restorelayout}{%
	\setlength{\parindent}{\vutinfth@tmp@parindent}%
	\setlength{\baselineskip}{\vutinfth@tmp@baselineskip}%
	\setlength{\parskip}{\vutinfth@tmp@parskip}%
}%
\newsetlength{\vutinfth@logo@offset@x}{10.6mm}%
\newsetlength{\vutinfth@logo@offset@y}{22mm}%
\newsetlength{\vutinfth@logo@width@safe}{74mm}%
\newsetlength{\vutinfth@logo@height}{11mm}%
\newsetlength{\vutinfth@header@width}{\paperwidth - \vutinfth@logo@offset@x - \vutinfth@logo@offset@x}%
\newsetlength{\vutinfth@header@height}{\vutinfth@logo@height}%
\newsetlength{\vutinfth@header@separator}{-12mm}%
\newcommand{\vutinfth@header@titlepage}{%
	\setlength{\unitlength}{1mm}%
	\begin{picture}(74, 11)%
		{\includegraphics[height=\vutinfth@logo@height]{Logo-schwarz.pdf}}
	\end{picture}\hfill
}%
\newcommand{\vutinfth@footer@titlepage}{%
	\centering
	\begin{minipage}{\textwidth}%
		\centering\vutinfth@normalsize\sffamily
		Technische Universit\"{a}t Wien\\
		A-1040 Wien \vutinfth@squarebullet\space
		Karlsplatz 13 \vutinfth@squarebullet\space
		Tel. +43-1-58801-0 \vutinfth@squarebullet\space
		www.tuwien.at%
	\end{minipage}%
}%
\makepagestyle{vutinfth@pagestyle@titlepage}%
\makerunningwidth{vutinfth@pagestyle@titlepage}[\textwidth]{%
	\vutinfth@header@width}%
\makeheadposition{vutinfth@pagestyle@titlepage}{%
	center}{center}{center}{center}%
\makeevenhead{vutinfth@pagestyle@titlepage}{}{%
	\vutinfth@header@titlepage}{}%
\makeoddhead{vutinfth@pagestyle@titlepage}{}{%
	\vutinfth@header@titlepage}{}%
\makefootrule{vutinfth@pagestyle@titlepage}{%
	\vutinfth@pagestyle@titlepagefootrunwidth}{0.5pt}{\footruleskip}%
\makeevenfoot{vutinfth@pagestyle@titlepage}{}{%
	\vutinfth@footer@titlepage}{}%
\makeoddfoot{vutinfth@pagestyle@titlepage}{}{%
	\vutinfth@footer@titlepage}{}%
\newsetlength{\vutinfth@bigskipamount}{6mm}%
\newcommand{\vutinfth@bigskip}{\vspace{\vutinfth@bigskipamount}}%
\newcommand{\AdvisorBlock}{%
	\ifundergraduate{%
		\begin{minipage}[t][2.5cm][t]{\textwidth}%
			\vutinfth@normalsize
			\begin{tabular}{@{}l@{ }l}%
				\vutinfth@polylingual@Advisor: &
				\vutinfth@person@advisor@fullname\\
				\ifdef{\vutinfth@person@firstassistant@def}{%
					\vutinfth@polylingual@Assistance: &
					\vutinfth@person@firstassistant@fullname\\
				}{}%
				\ifdef{\vutinfth@person@secondassistant@def}{%
					\ifundef{\vutinfth@person@firstassistant@def}{%
						\vutinfth@person@firstassistant@error
					}{%
						& \vutinfth@person@secondassistant@fullname\\
					}%
				}{}%
				\ifdef{\vutinfth@person@thirdassistant@def}{%
					\ifundef{\vutinfth@person@firstassistant@def}{%
						\vutinfth@person@firstassistant@error
					}{%
						\ifundef{\vutinfth@person@secondassistant@def}{%
							\vutinfth@person@secondassistant@error
						}{%
							& \vutinfth@person@thirdassistant@fullname\\
						}%
					}%
				}{}%
			\end{tabular}%
		\end{minipage}%
	}%
	\ifgraduate{%
		\begin{minipage}[t][1.6cm][t]{\textwidth}%
			\vutinfth@normalsize
			\vutinfth@polylingual@Advisor:
			\vutinfth@person@advisor@fullname
			\ifdef{\vutinfth@person@secondadvisor@def}{%
				\\
				\vutinfth@polylingual@Secondadvisor:
				\vutinfth@person@secondadvisor@fullname
			}{}%
		\end{minipage}\par%
	}%
}%
\newsetlength{\vutinfth@signature@height}{25mm}%
\newsetlength{\vutinfth@signature@width}{51mm}%
\newsetlength{\vutinfth@placedate@width}{50mm}%
\newcommand{\SignatureFields}[3][n]{%
	{\vutinfth@normalsize
		\ifstrequal{#1}{y}{%
			\begin{minipage}[b][\vutinfth@signature@height]{%
					\vutinfth@placedate@width
				}%
				\vutinfth@polylingual@Place,
				\DTMusedate{vutinfth@date@signing}\vspace*{\baselineskip}%
			\end{minipage}%
			\hfill
		}{}%
		\ifstrequal{#1}{n}{}{}%
		\ifstrequal{#1}{h}{%
			\hspace*{\vutinfth@placedate@width}%
			\hfill
		}{}%
		\ifstrempty{#2}{%
			\hspace*{\vutinfth@signature@width}%
			\hfill
		}{%
			\begin{minipage}[b][\vutinfth@signature@height]{%
					\vutinfth@signature@width
				}%
				\centering
				\rule{\vutinfth@signature@width}{0.5pt}\\
				#2%
			\end{minipage}%
			\hfill
		}%
		\ifstrempty{#3}{}{%
			\begin{minipage}[b][\vutinfth@signature@height]{%
					\vutinfth@signature@width
				}%
				\centering
				\rule{\vutinfth@signature@width}{0.5pt}\\
				#3%
			\end{minipage}%
		}%
	}%
}%

\newcommand{\ReviewerBlock}{%
	\ifgraduate{%
		{\vutinfth@normalsize
			\vutinfth@polylingual@Reviewed\\
			\SignatureFields[h]{%
				\vutinfth@person@firstreviewer@name
			}{%
				\vutinfth@person@secondreviewer@name
			}%
		}%
	}%
}%
\newcommand{\SignatureBlock}{%
	\ifundergraduate{%
		{\vutinfth@normalsize
			\SignatureFields[y]{%
				\vutinfth@person@author@name
			}{%
				\vutinfth@person@advisor@name
			}%
		}%
	}%
	\ifgraduate{%
		{\vutinfth@normalsize
			\SignatureFields[y]{}{%
				\vutinfth@person@author@name
			}%
		}%
	}%
}%
\newcommand{\AddTitlePage}{
	\thispagestyle{vutinfth@pagestyle@titlepage}%
	\newgeometry{%
		left=2.4cm,right=2.4cm,bottom=2.5cm,top=2cm,
		headsep=\vutinfth@header@separator,
		head=\vutinfth@header@height
	}%
	\vutinfth@savelayout
	\setlength{\parindent}{0pt}%
	\setlength{\baselineskip}{13.6pt}%
	\setlength{\parskip}{0pt plus 1pt}%
	\begin{SFFont}{phv}%
		\sffamily
		{\centering
			\vspace*{1.2cm}\par
			\begin{minipage}[t][5cm][b]{\textwidth}%
				\centering
				\vutinfth@HUGE{\bfseries\vutinfth@polylingual@Title}\\
				\bigskip
				\vutinfth@huge{\bfseries
					\ifdef{\vutinfth@polylingual@Subtitle}{%
						\vutinfth@polylingual@Subtitle}{%
					}%
				}%
			\end{minipage}\par
			\vutinfth@bigskip\vutinfth@bigskip
			{\vutinfth@LARGE\vutinfth@polylingual@thesisname}\par
			\vutinfth@bigskip
			{\vutinfth@large\vutinfth@polylingual@submission}\par
			\vutinfth@bigskip
			\ifundergraduate{%
				{\vutinfth@LARGE{\bfseries\vutinfth@polylingual@degreename}}\par
				\vutinfth@bigskip
				{\vutinfth@large\vutinfth@polylingual@in}\par
				\vutinfth@bigskip
				{\vutinfth@Large{\bfseries\vutinfth@polylingual@Curriculum}}\par
			}%
			\ifgraduate{%
				{\vutinfth@LARGE{\bfseries\vutinfth@polylingual@degreename}}\par
			}%
			\vutinfth@bigskip
			{\vutinfth@large\vutinfth@polylingual@by}\par
			\vutinfth@bigskip
			{\vutinfth@Large{\bfseries\vutinfth@person@author@fullname}}\par
			\smallskip
			{\vutinfth@large\vutinfth@polylingual@Registrationnumber\
				\vutinfth@data@regnumber}\par
		}%
		\vutinfth@bigskip\vutinfth@bigskip
		\begin{minipage}[b][1.6cm][c]{\textwidth}%
			\vutinfth@normalsize%
			\vutinfth@polylingual@faculty\par
			\vutinfth@polylingual@university
		\end{minipage}\par
		\AdvisorBlock\par
		\vfill
		\ReviewerBlock\par
		\SignatureBlock\par
		\vspace*{1cm}%
	\end{SFFont}%
	\pagestyle{empty}%
	\cleardoublepage
	\vutinfth@restorelayout
	\restoregeometry
}%
\newcommand{\AddStatementPage}{
	\vutinfth@savelayout
	\setlength{\parindent}{0pt}%
	\setlength{\baselineskip}{13.6pt}%
	\setlength{\parskip}{0pt plus 1pt}%
	\begin{SFFont}{phv}%
		\sffamily
		\chapter*{\vutinfth@polylingual@StatementChapter}%
		\vutinfth@person@author@fullname\par
		\vspace{1.2cm}%
		{\normalfont\vutinfth@polylingual@Statement}\par
		\vspace{1.2cm}%
		\SignatureFields[y]{\vutinfth@person@author@name}{}%
	\end{SFFont}%
	\cleardoublepage
	\vutinfth@restorelayout
}%
\newcommand{\addtitlepage}[1]{%
	\selectlanguage{#1}%
	\AddTitlePage
}%
\newcommand{\addstatementpage}{%
	\selectlanguage{naustrian}%
	\AddStatementPage
}%
\newenvironment{wledgements}{%
	\selectlanguage{english}%
	\chapter{wledgements}%
}{%
	\cleardoublepage
}%
\newenvironment{wledgements*}{%
	\selectlanguage{english}%
	\chapter*{wledgements}%
}{%
	\cleardoublepage
}%


\newenvironment{titlepage}{%
	\selectlanguage{naustrian}%
%	\chapter{Danksagung}%
}{%
	\clearpage
}%
\newenvironment{titelpage*}{%
	\selectlanguage{naustrian}%
%	\chapter*{Danksagung}%
}{%
	\clearpage
}%


\newenvironment{danksagung}{%
	\selectlanguage{naustrian}%
	\chapter{Danksagung}%
}{%
	\clearpage
}%
\newenvironment{danksagung*}{%
	\selectlanguage{naustrian}%
	\chapter*{Danksagung}%
}{%
	\clearpage
}%
\renewenvironment{abstract}{%
	\selectlanguage{english}%
	\chapter{Abstract}%
}{%
	\newpage
}%
\newenvironment{abstract*}{%
	\selectlanguage{english}%
	\chapter*{Abstract}%
}{%
	\newpage
}%
\newenvironment{kurzfassung}{%
	\selectlanguage{naustrian}%
	\chapter{Kurzfassung}%
}{%
	\newpage
}%
\newenvironment{kurzfassung*}{%
	\selectlanguage{naustrian}%
	\chapter*{Kurzfassung}%
}{%
	\newpage
}%
\newenvironment{eides}{%
	\selectlanguage{naustrian}%
	\chapter{Eidesstattliche Erklärung}%
}{%
	%\cleardoublepage%
}%
\newenvironment{eides*}{%
	\selectlanguage{naustrian}%
	\chapter*{Eidesstattliche Erklärung}%
}{%
	\cleardoublepage
}%
\makepagestyle{vutinfth@pagestyle@default}%
\makeevenfoot{vutinfth@pagestyle@default}{\thepage}{}{}%
\makeoddfoot{vutinfth@pagestyle@default}{}{}{\thepage}%
\aliaspagestyle{chapter}{vutinfth@pagestyle@default}%
\aliaspagestyle{part}{vutinfth@pagestyle@default}%
\addto\frontmatter{\pagestyle{vutinfth@pagestyle@default}}%
\addto\mainmatter{\pagestyle{Ruled}}%
\addto\backmatter{\pagestyle{vutinfth@pagestyle@default}}%
\endinput
%%
%% End of file `vutinfth.cls'.
