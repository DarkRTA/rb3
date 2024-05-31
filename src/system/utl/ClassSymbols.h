#ifndef UTL_CLASSSYMBOLS_H
#define UTL_CLASSSYMBOLS_H
#include "utl/Symbol.h"

// These symbols may overlap with the names of classes, so they're split out into here
// to avoid polluting every file that includes Symbols.h with them. Otherwise, errors
// result and a `class` prefix is required to disambiguate.

extern Symbol AmbientOcclusion;
extern Symbol Array;
extern Symbol BandButton;
extern Symbol BandFx;
extern Symbol BandLabel;
extern Symbol BandMeshLauncher;
extern Symbol BandPicture;
extern Symbol BandPlacer;
extern Symbol BandSlider;
extern Symbol BandTextEntry;
extern Symbol ButtonEx;
extern Symbol Cam;
extern Symbol Character;
extern Symbol CharacterTesting;
extern Symbol CharClip;
extern Symbol CharClipSamples;
extern Symbol CharTransCopy;
extern Symbol CharTransDraw;
extern Symbol CharWeightSetter;
extern Symbol Command;
extern Symbol CompositeTexture;
extern Symbol CubeTex;
extern Symbol DummyObjClass;
extern Symbol Float;
extern Symbol FloatVal;
extern Symbol Font;

extern Symbol Func;
extern Symbol Generator;
extern Symbol Glob;
extern Symbol Int;
extern Symbol LabelEx;
extern Symbol LayerDir;
extern Symbol Line;
extern Symbol Mat;

extern Symbol MeshAnim;
extern Symbol MeshGenerator;
extern Symbol Object;
extern Symbol ObjectDir;
extern Symbol P9TransDraw;
extern Symbol PanelDir;
extern Symbol ParticleSys;
extern Symbol PartLauncher;
extern Symbol PictureEx;
extern Symbol Placer;
extern Symbol PropAnim;
extern Symbol Property;
extern Symbol RenderedTex;

extern Symbol Slider;
extern Symbol String;
extern Symbol Sym;
extern Symbol SynthSample;
extern Symbol TestMicPanel;
extern Symbol TestName;
extern Symbol Tex;
extern Symbol TexMovie;
extern Symbol TexRenderer;
extern Symbol Text;
extern Symbol TextEntry;
extern Symbol TrackTesting;
extern Symbol UIPanel;
extern Symbol Unhandled;
extern Symbol Var;
extern Symbol WorldFx;
extern Symbol WorldInstance;
extern Symbol WorldObject;
extern Symbol Group;
extern Symbol Movie;
extern Symbol View;

#endif
