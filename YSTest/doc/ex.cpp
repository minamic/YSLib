// v0.3217; *Build 219 r71;
/*
$META:
//$configureation_for_custom_NPL_script_parser:
$parser
(
	$eval($ignore_not_impl);
	$eval($for_each $anything $in $.iterators $do_something) unfold;
);
$parser.$ __pstate;
$parser.unfold __unfold;
$parser.$.iterators __iterators;

__unfold.$ctor $=
(
	__pstate.behavior.ignore $= $true;
);
__unfold.$dtor $=
(
	__pstate.behavior.ignore $= $false;
);
__unfold __iterators.for_labeled_paragraph
(
	$DONE,
	$DOING,
	$NEXT_TODO,
	$LOW_PRIOR_TODO,
	$KNOWN_ISSUE,
	$TODO
);

$script_preprocessor_escapse:
//$Record prefix and abbrevations:
$parser.$preprocessor.$define_schema "<statement> ::= $statement_in_literal";
; ::= statement termination
= ::= equivalent
+ ::= added
- ::= removed
* ::= fixed
/ ::= modified
% ::= identifier
~ ::= from
! ::= not
& ::= and
| ::= or
^ ::= used
-> ::= changed to
>> ::= moved to
=> ::= renamed to
<=> ::= swapped names
@ ::= in / belonged to
\a ::= all
\ab ::= abstract
\ac ::= access
\adtor ::= abstract destructor
\amb ::= ambiguities
\amf ::= abstract/pure virtual member function
\arg ::= arguments
\as ::= assertions
\bg ::= background
\c ::= const
\cb ::= catch blocks
\cl ::= classes
\clt ::= class templates
\conf ::= configuration
\cp ::= copied
\ctor ::= constructors
\ctort ::= constuctor templates
\cv ::= const & volatile
\d ::= derived
\de ::= default
\def ::= definitions
\dep ::= dependencies
\decl ::= declations
\dir ::= directories
\doc ::= documents
\dtor ::= destructors
\e ::= exceptions
\em ::= empty
\en ::= enums
\eh ::= exception handling
\err ::= errors
\es ::= exception specifications
\evt ::= events
\evh ::= event handling
\ex ::= extra
\exc ::= excluded
\ext ::= extended
\exp ::= explicit
\expr ::= expressions
\f ::= functions
\fn ::= \f
\ft ::= function templates
\fw ::= forward
\g ::= global
\gs ::= global scpoe
\h ::= headers
\i ::= inline
\impl ::= implementations
\in ::= interfaces
\init ::= initializations
\inc ::= included
\inh ::= inherited
\inv ::= invoke
\k ::= keywords
\lib ::= library
\ln ::= lines
\m ::= members
\mac ::= macros
\mem ::= memory
\mf ::= member functions
\mft ::= member function templates
\mg ::= merged
\mo ::= member objects
\mt ::= member templates
\n ::= names
\ns ::= namespaces
\o ::= objects
\op ::= operators
\or ::= overridden
\param ::= parameters
\param.de ::= default parameters
\pre ::= prepared
\proj ::= projects
\pt ::= points
\ptr ::= pointers
\q ::= qualifiers
\rem ::= remarked
\ren ::= renamed
\ref ::= references
\refact ::= refactorings
\res ::= resources
\ret ::= return
\s ::= static
\scm ::= static const member
\sf ::= non-member static functions
\simp ::= simplified
\sm ::= static member
\smf ::= static member functions
\smft ::= static member function templates
\snm ::= static non-member
\spec ::= specifications
\st ::= structs
\str ::= strings
\stt ::= struct templates
\t ::= templates
\tb ::= try blocks
\tg ::= targets
\tr ::= trivial
\tp ::= types
\u ::= units
\un ::= unnamed
\v ::= volatile
\vt ::= virtual
\val ::= values

$using:
\u YObject
(
	\cl YObject,
	\cl YCountableObject,
	\clt GDependence
),
\u YShell
(
	\cl YShell
),
\u YApplication
(
	\cl YLog,
	\cl YApplication
),
\u YConsole
(
	\cl Console
),
\u YWidget
(
	\in IWidget,
	\cl Visual,
	\cl Widget
),
\u YLabel
(
	\cl MLabel,
	\cl Label,
	\cl MTextList
),
\u YUIContainer
(
	\in IUIBox,
	\in IUIContainer,
	\cl UIContainer
),
\u YControl
(
	\in IControl,
	\cl Control
),
\u YPanel
(
	\in IPanel,
	\cl Panel
)
\u YWindow
(
	\in IWindow,
	\cl MWindow,
	\cl AWindow,
	\cl AFrame,
	\cl Frame
),
\u YGUI
(
	\cl YGUIShell,
)
\u UIContainerEx
(
	\cl AUIBoxControl,
),
\u Form
(
	\cl Form;
),
\u Button
(
	\cl Thumb,
	\cl Button
),
\u CheckBox
(
	\cl CheckBox
),
\u TextList
(
	\cl TextList
),
\u Menu
(
	\u Menu
),
\u Scroll
(
	\cl ATrack,
	\cl HorizontalTrack,
	\cl VerticalTrack,
	\cl MScrollBar,
	\cl AScrollBar,
	\cl HorizontalScrollBar,
	\cl VerticalScrollBar
),
\u ListBox
(
	\cl ListBox,
	\cl FileBox,
);


$DONE:
r1:
- \inc \h "../Core/yres.h" @ \h Form;
- \inc \h "ygdi.h" @ \impl \u YDevice;
/ \u (YResource & YGDI) >> \dir Service ~ \dir Core;
/ \u YText >> \dir Service ~ \dir UI;
/ \tr \inh \h @ (\h (YPanel & YStyle & YWidget & DSReader & YLabel)
	& \impl \u ListBox);
/ @ \h YGDI:
	- \inc \h "../Core/ycutil.h";
	+ \inh \h <ystdex/iterator.hpp>;
/ @ \h YAdaptor:
	- \inc \h <ystdex/iterator.hpp>;
	- \inc \h <ystdex/cast.hpp>;
+ \inc \h <ystdex/cast.hpp> @ \h YUIComponent;

r2:
/ \clt GMRange @ \ns YSLib::Components::Controls @ \h YControl
	>> \ns YSLib @ \h YObject;

r3:
/ typedef \en (Rotation & Orientation) @ \h YGDI >> \h YGDIBase;

r4:
/ @ \dir Service:
	+ \u YBlit["yblit.h", "yblit.cpp"];
	+ \u YDraw["ydraw.h", "ydraw.cpp"];
	/ (\a typedef & \stt (PixelFiller & SequenceTransformer
		& VerticalLineTransfomer) & \a (\f & \t) 'Blit*' & \i \ft ClearPixel
		& \a (\f & \t) 'Fill*' & \c \o 'BLT_*' & \a (\f & \t) 'blit*'
		& \t TransformRect & \f CopyBuffer & \f ClearImage)
		\exc ('BlitTo' & \f FillRect) @ \u YGDI >> \u YBlit;
	/ \f \i PutPixel & \a \f 'Draw*' @ \u YGDI >> \u YDraw;
	+ \inc \h YBlit @ \impl \u (YDraw & YGDI);
	+ \inc \h YBlit @ \impl \u YText;
	- \inc \h YFont @ \h (YText & YBlit & YDraw);
* \tr \mac 'YSL_INC_*';
- \h <ystdex/iterator.hpp> @ \h (YGDI & YDraw);
/ \inc \h YGDI -> YDraw @ \h (YStyle & YWidget);
+ \inc \h YBlit @ \h YWindow;

r5:
/= test 1 ^ \conf release;

r6:
/ @ \u YUIContainer:
	/ \f Point LocateOffset(const IWidget*, Point, const IWindow*)
		-> \f Point LocateOffset(const IWindow*, const IWidget*, Point);
	/ \tr \impl @ \f (LocateWindowOffset & LocateForWindow & LocateForDesktop
		& Fill);
	/ swap \param @ \f LocateForWidget;
/ \tr \impl @ \f DrawWidgetBounds @ \u YStyles;
/ \tr \impl @ \mf YGUIShell::ResponseTouchBase;

r7:
/ \simp & optimized \impl @ \mf YGUIShell::ResponseTouchBase;

r8:
/ @ \impl \u YUIContainer:
	/ \f GetContainersListFrom @ \un \ns \mg -> \f LocateForWidget;
	/ optimized \impl @ \f LocateForWidget ^ list ~ map;
/ \impl @ \mf MenuHost::Contains;

r9:
/= test 2 ^ \conf release;

r10:
/ (\m FontCache* pFontCache & \mf (ResetFontCache & DestroyFontCache
	& GetFontCache)) @ \cl YApplication @ \u YApplication
	>> \cl YDSApplication @ \u YGlobal;
/ \tr \impl @ \ctor @ \cl (YApplication & YDSApplication);
/ \tr \impl @ (\f FetchDefaultTypeface & \mf FontCache::GetDefaultTypefacePtr)
	@ \impl \u YFont;
/ \tr \impl @ \f (InitializeSystemFontCache & CheckSystemFontCache)
	@ \impl \u YShellInitialization;
/ \tr \impl @ \f main \impl \u YGlobal;
/ \tr @ \de \arg @ \decl @ \ctor @ \cl MDualScreenReader @ \h DSReader;
/ \tr \impl @ \mf ShlExplorer::TFormExtra::OnClick_btnDragTest
	@ \impl \u Shells;

r11:
/ @ \h YGlobal:
	+ \f \i Devices::Screen& FetchDefaultScreen();
	+ \f \i FontCache& FetchDefaultFontCache();
	- using Devices::DSScreen;
/ \impl @ (\f FetchDefaultTypeface & \mf FontCache::GetDefaultTypefacePtr)
	@ \impl \u YFont ^ FetchDefaultScreen;
/ \de \arg @ \decl @ \ctor @ \cl Console ^ FetchDefaultScreen;
/ \tr \impl @ \f (InitializeSystemFontCache & CheckSystemFontCache)
	@ \impl \u YShellInitialization ^ FetchDefaultScreen;
* \doc group @ \stt xcrease_t @ \h Utilities;
/ \tr @ \impl \u YGlobal ^ using Devices::DSScreen;

r12:
/= test 3 ^ \conf release;

r13:
/ optimized \impl @ \f CreateSharedScreenImage @ \impl \u YShellHelper
	^ rvalue \ref;

r14:
/ \impl @ \f LoadL @ \un \ns @ \impl \u Shells;

r15:
/ @ \un \ns @ \impl \u Shells:
	+ \f BitmapPtr FetchGlobalImageBuffer(size_t);
	/ \impl @ \a \f 'Load?' ^ FetchGlobalImageBuffer;
/ @ \cl MTextList:
	/ \m mutable shared_ptr<ListType> pList => hList;
	/ \tr @ \mf GetList;
	/ \tr \impl @ \ctor;

r16:
/ @ \un \ns @ \impl \u Shells:
	/ \a \f 'Load?' ^ FetchGlobalImageBuffer \mg -> \f FetchImage;
	/ FetchGlobalImage
	- unused \o BitmapPtr gbuf;

r17:
- \f CreateSharedScreenImage @ \u YShellHelper;

r18-r19:
/ \impl @ \mf YMainShell::OnActivated @ \impl \u Shells;

r20-r22:
/ \impl @ \ctor @ \cl ShlExplorer::TFormTest @ \impl \u Shells;

r23:
/ \impl @ \mf YMainShell::OnActivated @ \impl \u Shells;

r24:
/ \impl @ \mf OnActivated @ \cl (YMainShell & ShlExplorer) @ \impl \u Shells;

r25-r26:
/= test 4;

r27:
/ \impl @ \mf YMainShell::OnActivated @ \impl \u Shells;

r28-r49:
/= test 5;

r50:
/ \simp \impl @ \mf YMainShell::OnActivated @ \impl \u Shells;

r51-r52:
* "wrong default argument of desktop backgrond color" $since b160:
	/ \ctor \exp Desktop(Devices::Screen&, Color = 0, const
		shared_ptr<Drawing::Image>& = shared_ptr<Drawing::Image>()) -> \exp
		Desktop(Devices::Screen&, Color = Drawing::ColorSpace::Black,
		const shared_ptr<Drawing::Image>& = shared_ptr<Drawing::Image>());

r53-r54:
/ \impl @ \mf YMainShell::OnActivated @ \impl \u Shells;

r55:
/= test 6 ^ \conf release;

r56:
/ @ \impl \u Shells:
	+ \cl ProgressBar @ \un \ns;
	/ \impl @ \mf YMainShell::OnActivated;

r57:
* \impl @ \mf ProgressBar::Paint @ \un \ns @ \impu \u Shells;

r58:
/ \impl @ \mf YMainShell::OnActivated @ \impl \u Shells;

r59-r67:
/ test 7;

r68:
* \impl @ \mf YMainShell::OnActivated @ \impl \u Shells;

r69:
/ \impl @ \mf YMainShell::OnActivated @ \impl \u Shells;

r70:
+ \u Progress["progress.h", "progress.cpp"] @ \dir UI;
/ \cl ProgressBar @ \un \ns @ \impl \u >> \ns Components::Widgets
	@ \u Progress;
+ \inh \h <YSLib/UI/progress.h> @ \impl \u Shells;

r71:
/= test 8 ^ \conf release;


$DOING:

$relative_process:
2011-06-20:
-18.9d;
//Mercurial rev1-rev89: r4409;

/ ...


$NEXT_TODO:
b220-b324:
^ unique_ptr ~ GHandle @ \clt GEventMap @ \h YEvent avoiding patching
	libstdc++ for known associative container operation bugs:
	- \rem @ \impl @ \mft GetEvent @ \clt EventMap @ \h YEvent;
* non-ASCII character path error in FAT16;
+ key accelerators;
+ \impl styles @ widgets;
/ fully \impl \u DSReader;
	* moved text after setting lnGap;

b325-b768:
+ data configuragion;
/ impl 'real' RTC;
/ text alignment;
+ \impl pictures loading;
/ improve efficiency @ \ft polymorphic_crosscast @ \h YCast;
+ correct DMA (copy & fill);
* platform-independence @ alpha blending:
	+ \impl general Blit algorithm;
+ shared property: additional;
+ GDI brushes;
/ user-defined bitmap buffer @ \cl Desktop;


$LOW_PRIOR_TODO:
b769-b1536:
+ (compressing & decompressing) @ gfx copying;
+ Microsoft Windows port;
+ general component operations:
	+ serialization;
	+ designer;
+ database interface;


$KNOWN_ISSUE:
* fatal \err @ b16x:
[
F:\Programing\GadgetLib>F:\devkitPro\devkitARM\bin\arm-eabi-addr2line.exe -f -C
	-e F:\Programing\NDS\YSTest\YSTest\arm9\YSTest.arm9.elf -s -i 02055838
	ftc_snode_weight
	ftcsbits.c:271
]
* fatal \err @ since b177 when opening closed lid @ real DS:
[
b185:
F:\Programing\GadgetLib>F:\devkitPro\devkitARM\bin\arm-eabi-addr2line.exe -f -C
-e F:\Programing\NDS\YSTest\YSTest\arm9\YSTest.arm9.elf -s -i 02037F04
guruMeditationDump
gurumeditation.c:229
b186 r17[realease]:
pc: 09529334, addr: 09529334;
b187 r18[debug]:
pc: 020227C8, addr: 0380FDA4;
F:\Programing\GadgetLib>F:\devkitPro\devkitARM\bin\arm-eabi-addr2line.exe -f -C
-e F:\Programing\NDS\YSTest\YSTest\arm9\YSTest.arm9.elf -s -i 020227C8
guruMeditationDump
gurumeditation.c:254
]


$TODO:

Clarify the log levels.

Make "UpdateFont()" more efficienct.

More efficient %YTextRegion output:
Use in-buffer background color rendering and function %CopyToScreen()
	to inplements %YTextRegion background;
Use pre-refershing to make font changing.

Consider to simplify the general window class: @YForm.

Build a more advanced console wrapper.

Build a series set of robust gfx APIs.

More GUI features needed:
Icons;
Other controls.

Other stuff to be considered to append:
Design by contract: DbC for C/C++, GNU nana.


$HISTORY:

$parser.state.old_style $= $false;
$design; // features changing only made sense to library developers;
$doc; // for documents target;
$add_features +; // features added;
$fix_bugs *; // bugs fixed;
$modify_features /; // features modified;
$remove_features -; // features removed;
$using ^; // using;
$source_from ~; // features replacing from;
$belonged_to @;
$moved_to >>;
$renamed_to =>;

//$transform $list ($list_member $pattern $all($exclude $pattern \
//	$string_literal "*")) +;

$ellipse_refactoring;

$now
(
	/ $design "unit %YGUI decomposed for Blit and 2D API",
	/ "optimized widget-to-widget locating",
	/ $design "font cache moved to platform-dependent application class from
		class %YApplication",
	+ "several global helper functions as platform-independent interface",
	+ "mutiple background switch test",
	* "wrong default argument of desktop backgrond color" $since b160,
	+ "widgets: progress bar" @ "class %ProgressBar"
),

b218
(
	+ "desktop background switch test",
	+ $design "ownership tag structure",
	- $design "global resource helper functions",
	+ "DS screen class",
	^ "class %YMainShell for resource loading" ~ "class %ShlLoad",
	- "class %ShlLoad"
),

b217
(
	* "wrong lost focus behavior for menus \
		which had popped submenu(s) previously" $since b214,
	/ "improved compatibility" @ "class %GHEvent for types \
		not met EqualityComparable requirement interface \
		including closure types" $=
	(
		/ "result always true",
		* "compile-error for non-trivally copy-assignable objects",
		/ "optimized implementation to avoid bloat code instantialized"
	),
	+ $design "Code::Blocks project files" $=
	(
		+ "workspace file",
		+ "project files"
	),
	/ $design ^ "lambda expression" ~ "several private member function \
		as event handlers",
	+ "%KeyDown and %KeyHeld handlers for scroll bars \
		to perform mapped touch behaviors",
	+ "key to touch event mapping methods" @ "class %Control",
	* "wrong behavior" @ "track touch held event handler" $since b213 $=
	(
		* "wrong coordinate passed to touch focus captured control" $since b195;
	),
	+ $design "cscope file"
),

b216
(
	/ $design "header file dependencies",
	/ "focused boundary for controls",
	* "strict ISO C++2011 code compatibility" $=
	(
		* "deprecated keyword static using in ISO C++2003 now removed but"
			^ @ unit "YApplication when macro YSL_DEBUG_MSG defined"
	),
	/ "more efficient message queue implementation" ^ "%multiset"
		~ %priority_queue",
	/ "simplified shell example",
	+ "default windows Z order",
	+ "message fetching automatically calling %Idle \
		when size less or equal than a user-specified limit"
),

b215
(
	+ "disabled state style of control %Thumb",
	* "disabled control touch event handling" $b199,
	+ "checkbox and disabling test",
	+ "visible arrow indicating multi-level menus",
	/ "creating list" @ ("constructor of class %MTextList"
		~ "member function %GetList"),
	+ "event handler supporting for types not met EqualityComparable
		requirement interface including closure types",
	* $design "access of interitance of class std::function"
		@ "class template %GHEvent" $since b207,
	+ "disabled behavior test" @ "%ShlExplorer",
	/ "thumb/button boundary style",
	/ "global architecture" $=
	(
		/ "screen constant" >> "namespace scope" ~ "class %Global",
		+ "class %YDSApplication" ~ "class %Global",
		- "singleton mechanism" @ "class %YApplication"
	)
),

b214
(
	/ "functions of menus" $=
	(
		+ "hiding on confirmed",
		+ "resizing with width of text in list",
		/ "margin of menus",
		+ "submenus" $=
	),
	* $design "exception specification" @ "unit %YApplication",
	/ $doc $=
	(
		* "template parameter description" $since b189 $=
		(
			^ "\tparam" ~ "\param"
		),
		* "\defgroup description spell error" $since b209,
		* $design "operator new & delete conmments" $since b203,
		/ "simplified doxygen file excluded paths"
	),
	/ $design ^ "public %noncopyable inheritance"
		~ "all private %noncopyable inheritance",
	* "point containing test for zero width or height rectangle \
		turned out asseration failure" $since b204,
	* "constness of text width mersuring" $since b197,
	/ "simplified focus operations interface" $=
	(
		- "unused parameter and argument"
	)
),

b213
(
	* $design "UI assertion strings",
	* "menu colors",
	* "touch event coordinate error" @ "contianer controls" $since b195,
	+ "functions of menus" $=
	(
		+ "resizing for content",
		+ "hiding when focus lost"
	),
	+ "predicator %Contains" @ "UI container implementation"
),

b212
(
	/ $design "assertion strings",
	/ "menu constructor",
	+ "redundant menu state member" @ "class %Menu",
	/ "container member APIs" ^ "reference parameter" ~ "pointer parameter",
	* "constructor of class %Frame",
	+ "Z order for widget overlaying" @ " UI containers",
	+ "menu laid at top level" ^ "Z order"
),

b211
(
	/ "implemented messages with general object content holder"
		^ "non-pointer member" ~ "%shared_ptr",
	+ "message content mapping",
	/ $design "messaging APIs" >> "unit YApplication" ~ "unit YShell",
	/ "test menu fixed on the desktop"
),

b210
(
	+ "template %is_valid for checking pointers which cast bool explicitly",
	/ "part of template %raw moved to namespace %ystdex",
	- $design "some unused code",
	+ "macro %yforward for simply using std::forward and argument \
		type deduction",
	/ "handles and smart pointers rearranged" $=
	(

		- "%GHWeak",
		^ "%std::shared_ptr" ~ "%GHandle",
		- "%GHandle"
	),
	/ "implementation of messages" $=
	(
		/ "implementation of class %Message",
		- "message ID mapping"
	)
),

b209
(
	/ "merged library CHRLib" >> "library YCLib",
	/ $design "protected function inheritance" @ "class template %GHEvent",
	/ "using directive of namespace %ystdex" @ "library YSLib",
	+ "lost %Rect operations",
	* "strict ISO C++2003 code compatibility" $=
	(
		^ "fixed macros" @ "header YFont"
	),
	/ "renamed directory %Shell to %UI @ "library YSLib",
	/ "several memory utilities for std::shared_ptr and std::unique_ptr"
		>> "library YCLib::YStandardExtend"
),

b208
(
	^ "rvalue references as parameter types of event handlers",
	/ "set default font size smaller",
	+ "vertical alignment" @ "labeled controls",
	* "fatel error" @ "direct UI drawing testing"
),

b207
(
	/ $design "event handler implementation ^ std::function" ~ "Loki::Function",
	- "library AGG",
	- "library Loki",
	+ $design "union %no_copy_t and union %any_pod_t for supressing \
		static type checking",
	+ $design "polymorphic function object template and base class",
	- "single-cast event class template",
	^ "rvalue reference" @ "event class",
	* "ystdex algorithms",
	* "minor event handler parameter type mismatch" @ "test code",
	* "key events response(added as %KeyDown, but removed as %KeyPress)"
		@ "project YSTest_ARM9" $since b201,
	* "tunnel and direct key and touch response repeated" @ "class %YGUIShell"
		$since b198
),

b206
(
	+ "menu test button",
	/ "file API",
	* "strict ISO C++2003 code compatibility" $=
	(
		+ "function %memcmp declation" @ "namespace %ystdex"
	),
	* "strict ISO C++2011 code compatibility" $=
	(
		* "implicit narrowing conversion(N3242 8.5.4/6) \
			in C++2011(N3242 5.17/9)" ^ "explicit static_cast",
		/ "character types" @ "header platform.h"
	),
	/ "coding using limited C++2011 features" $=
	(
		/ $design ^ "C++2011 style nested template angle brackets",
		/ $design ^ "keyword %auto",
		/ ^ "C++2011 type_traits" @ "namespace std" ~ "std::tr1"
	),
	- "Loki type operations",
	/ ^ "namespace %ystdex" @ "namespace %YSLib"
),

b205
(
	/ "simplified widgets and controls inheritance",
	/ "simplified image resource type",
	/ $design "protected inheritance of module classes except \
		%MScreenPositionEventArgs",
	/ "listbox highlight text color"
),

b204
(
	/ "weak handle improvement",
	/ $design "exception specification macro",
	- "window handles" $=
	(
		- "type %HWND",
		^ "%IWindow*" ~ "%HWND"
	),
	* "track background painting ignored" $since b191,
	+ "class %nullptr_t" @ "namespace ystdex",
	^ "nullptr at YSLib",
	/ $design "widgets virtual member functions"
),

b203
(
	/ $design "units rearrangement",
	/ $design "global architecture" $=
	(
		+ "global instance function",
		- "all global objects",
		- "platform dependent global resource" @ "class %YApplication",
		- "global object" @ "unit YNew"
	),
	+ "class %MTextList",
	/ "class %YSimpleText List using class %MTextList inheritance",
	/ "class %YSimpleText renamed to %YMenu",
	/ "using std::tr1::shared_ptr" ~ "smart pointers" @ "library Loki"
),

b202
(
	/ $design "unit renaming",
	/ "improvoed windows painting efficiency",
	* "buffered coordinate delayed in painting dragged control" $since b169
),

b201
(
	/ "focused button style",
	+ "key helding response" @ "class %ShlReader",
	+ "GDI API %BlitTo",
	/ "widgets drawing",
	/ $design "GDI API %CopyTo",
	+ "controls: panel",
	/ $design "YCLib" $=
	(
		+ "partial version checking for compiler and library implementation",
		+ "minor macros" @ "library YCLib",
	),
	+ "type conversion helper template",
	+ $design "implicit member overloading by interface parameter with type \
		%IControl and %IWidget" @ "container classes"
),

b200
(
	* "direct drawing test",
	/ "test UI view",
	* "%KeyHeld response" $since b199,
	+ "direct desktop drawing for %ShlSetting"
),

b199
(
	+ "event routing for %KeyUp, %KeyDown and %KeyHeld",
	* "event behavior with optimizing" $since b195,
	+ "keypad shortcut for file selecter",
	+ $design "returning number of called handles in event calling"
),

b198
(
	* "font caching without default font file load successfully",
	+ "showing and hiding windows",
	* "%ListBox scroll bar length",
	* "handle constructors",
	/ $design "shells for DS" $=
	(
		- "class %ShlGUI" @ "unit Shell_DS"
	),
	/ $design "using pointers" ~ "references in parameters \
		of container methods",
	/ "simplified GUI shell" $=
	(
		/ "input points matching",
		- "windows list"
	),
	/ $design "simplified destructors",
	/ "simplified window drawing",
	+ "desktop capability of non-control widget container",
	- "contianer pointer parameter" @ "constructor widgets",
	/ "desktops as window" @ "shells"
),

b197
(
	* "label alignment",
	+ "%std::string based font cache"
),

b196
(
	+ "controls: checkbox",
	* "platform color type",
	+ "horizontal text alignment" @ "class %MLabel"
),

b195
(
	* $design "makefiles",
	+ "dependency events",
	+ "simple events routing"
),

b170_b194
(
	+ "controls: tracks",
	+ "controls: scroll bars",
	+ "controls: scrollable container",
	+ "controls: listbox"
),

b159_b169
(
	+ "controls: buttons" @ "class (%YThumb, %YButton)",
	+ "controls: listbox class",
	+ "events"
),

b132_b158
(
	+ $design "core utility templates",
	+ "smart pointers using Loki",
	+ "Anti-Grain Geometry test",
	+ "GUI focus",
	+ "shells",
	+ "base abbreviation macros",
	+ "controls",
	+ "virtual inheritance" @ "control classes",
	+ "exceptions",
	+ "debug macros & functions",
	+ "color type",
	+ "class template %general_cast",
	+ "timer class"
),

b1_b131
(
	+ "initial test with PALib & libnds",
	+ "shell classes",
	+ "the application class",
	+ "CHRLib: character set management",
	+ "fonts management using freetype 2",
	+ "YCLib: platform independence",
	+ "basic objects & counting",
	+ "global objects",
	+ "string class",
	+ "file classes",
	+ "dual screen text file reader framework",
	+ "output devices & desktops",
	+ "messaging",
	+ "program initialization",
	+ "simple GUI: widgets & windows",
	+ "simple GDI",
	+ "simple resource classes"
);


*/
//---- temp code;
/*

	static YTimer Timer(1250);

	if(Timer.Refresh())
	{
	//	InitYSConsole();
	//	YDebugBegin();
		iprintf("time : %u ticks\n", GetTicks());
		iprintf("Message : 0x%04X;\nPrior : 0x%02X;\nObj : %d\n"
			"W : %u;\nL : %lx;\n", msg.GetMessageID(),
			msg.GetPriority(), msg.GetObjectID(), msg.GetWParam(),
			msg.GetLParam());
		WaitForInput();
	//	StartTicks();
	}*/
/*
	YDebugBegin();
	iprintf("time : %u ticks\n", GetTicks());
	iprintf("Message : 0x%04X;\nPrior : 0x%02X;\nObj : %d\n"
		"W : %u;\nL : %lx;\n", msg.GetMessageID(), msg.GetPriority(),
		msg.GetObjectID(), msg.GetWParam(), msg.GetLParam());
	WaitForInput();*/
/*
		InitYSConsole();
		iprintf("%d,(%d,%d)\n",msg.GetWParam(),
			msg.GetCursorLocation().X, msg.GetCursorLocation().Y);
*/

