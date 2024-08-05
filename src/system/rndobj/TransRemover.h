#pragma once

class RndTransformableRemover : public RndTransformable {
public:
    RndTransformableRemover(){}
    virtual Symbol ClassName() const { return ""; }
    virtual ~RndTransformableRemover(){}
};