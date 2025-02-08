#pragma once
#include "rndobj/Highlightable.h"
#include "obj/Object.h"
#include "math/Sphere.h"
#include "math/Mtx.h"
#include "math/Geo.h"
#include "utl/MemMgr.h"
#include <list>

class RndCam;

enum HighlightStyle {
    kHighlightWireframe,
    kHighlightSphere,
    kHighlightNone,
    kHighlightWireframeWithNormals,
    kNumHighlightStyles
};

/**
 * @brief An object that is drawable.
 * Original _objects description:
 * "Base class for drawable objects. Draw objects either
 * render polys or determine rendering state."
 */
class RndDrawable : public virtual RndHighlightable {
public:
    struct Collision {
        Collision() {}
        Collision(RndDrawable *o, float d, const Plane &p)
            : object(o), distance(d), plane(p) {}
        RndDrawable *object; // offset 0x0, size 0x4
        float distance; // offset 0x4, size 0x4
        Plane plane; // offset 0x10, size 0x10
    };

    RndDrawable();
    OBJ_CLASSNAME(Draw);
    OBJ_SET_TYPE(Draw);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    /** "Calculates the bounding sphere for the object." */
    virtual void UpdateSphere() { mSphere.Zero(); }
    virtual float GetDistanceToPlane(const Plane &, Vector3 &) { return 0.0f; }
    virtual bool MakeWorldSphere(Sphere &, bool) { return 0; }
    virtual RndCam *CamOverride() { return 0; }
    virtual void Mats(std::list<class RndMat *> &, bool) {}
    virtual void Draw();
    virtual void DrawShowing() {}
    virtual bool DrawShowingBudget(float);
    /** Get the list of this Object's children that are drawable. */
    virtual void ListDrawChildren(std::list<RndDrawable *> &) {}
    virtual RndDrawable *CollideShowing(const Segment &, float &, Plane &) { return 0; }
    virtual int CollidePlane(const Plane &);
    virtual void CollideList(const Segment &, std::list<Collision> &);
    virtual void DrawPreClear() {}
    virtual void UpdatePreClearState() {}
    virtual void Highlight();
    virtual ~RndDrawable() {}

    bool DrawBudget(float);
    bool CollideSphere(const Segment &);
    RndDrawable *Collide(const Segment &, float &, Plane &);

    bool Showing() const { return mShowing; }
    void SetShowing(bool b) { mShowing = b; }
    void SetOrder(float f) { mOrder = f; }
    const Sphere &GetSphere() const { return mSphere; }
    void SetSphere(const Sphere &s) { mSphere = s; }
    float GetOrder() const { return mOrder; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    static void DumpLoad(BinStream &);
    static HighlightStyle sHighlightStyle;
    static float sNormalDisplayLength;
    static bool sForceSubpartSelection;

    static HighlightStyle GetHighlightStyle() { return sHighlightStyle; }
    static void SetHighlightStyle(HighlightStyle hs) { sHighlightStyle = hs; }
    static float GetNormalDisplayLength() { return sNormalDisplayLength; }
    static void SetNormalDisplayLength(float f) { sNormalDisplayLength = f; }
    static bool GetForceSubpartSelection() { return sForceSubpartSelection; }
    static void SetForceSubpartSelection(bool b) { sForceSubpartSelection = b; }

    /** Handler to copy another RndDrawable's sphere to this one's.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents:
     *     Node 2: the other RndDrawable.
     * Example usage: {$this copy_sphere other_obj}
     */
    DataNode OnCopySphere(const DataArray *arr);
    /** Handler to retrieve this RndDrawable's sphere properties.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents:
     *     Nodes 2-5: vars to house this sphere's center X/Y/Z coordinates and radius.
     * Example usage: {$this get_sphere $x $y $z $radius}
     */
    DataNode OnGetSphere(const DataArray *arr);
    /** Handler to set whether or not this RndDrawable is showing.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents:
     *     Node 2: a boolean for showing or hiding.
     * Example usage: {$this set_showing TRUE}
     */
    DataNode OnSetShowing(const DataArray *arr);
    /** Handler to get whether or not this RndDrawable is showing.
     * @returns True if showing, false if not.
     * Example usage: {$this showing}
     */
    DataNode OnShowing(const DataArray *);
    /** Handler to zero this RndDrawable's sphere.
     * Example usage: {$this zero_sphere}
     */
    DataNode OnZeroSphere(const DataArray *);

    /** "Whether the object and its Draw children are drawn or collided with." */
    bool mShowing : 1;
    /** "Sort by distance to current camera per frame.
     * This has a CPU cost if there are many objects."
     */
    bool mSortInWorld : 1; // used in RndGroup
    /** "enable/disable the emitter" */
    bool mSynthEmitterEnabled : 1; // used in SynthEmitter
    bool mTestDone : 1; // used in RndFlare
    bool mLastDone : 1; // used in RndFlare
    bool mLineHasCaps : 1; // used in RndLine
    bool mLinePairs : 1; // used in RndLine
    bool mLineUpdate : 1; // used in RndLine

    bool mHasAOCalc : 1; // used in RndMesh
    /** "Whether or not to keep mesh vertices and faces.  Mutable meshes will always keep
     * this data." */
    bool mKeepMeshData : 1; // used in RndMesh
    bool mUseCachedBoxLightColors : 1; // used in RndMesh
    bool mForceNoQuantize : 1; // used in RndMesh
    bool mModulateColor : 1; // used in RndMultiMesh
    bool mUseCurrentRect : 1; // used in RndScreenMask
    bool unk9p6 : 1; // used in RndTexBlender
    bool mFrameDrive : 1; // used in RndParticleSys

    bool mPauseOffscreen : 1; // used in RndParticleSys
    bool mBubble : 1; // used in RndParticleSys
    bool mPreSpawn : 1; // used in RndParticleSys
    bool unkap3 : 1;
    bool mSpin : 1; // used in RndParticleSys
    bool mRandomDirection : 1; // used in RndParticleSys
    bool mVelocityAlign : 1; // used in RndParticleSys
    bool mStretchWithVelocity : 1; // used in RndParticleSys

    bool mConstantArea : 1; // used in RndParticleSys
    bool mPerspective : 1; // used in RndParticleSys
    bool unkbp2 : 1;
    bool mTextMarkup : 1; // used in RndText
    bool unkbp4 : 1; // used in RndText
    bool unkbp5 : 1; // used in RndText
    bool unkbp6 : 1; // used in RndText
    bool unkbp7 : 1; // used in RndText

    /** "bounding sphere" */
    Sphere mSphere; // 0xc
    /** "Draw order within proxies, lower numbers are drawn first,
     * so assign numbers from the outside-in (unless translucent), to minimize overdraw.
     * In groups, draw_order will be ignored unless you explicitly click the sort button."
     */
    float mOrder; // 0x1c
};
