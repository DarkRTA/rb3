#ifndef METABAND_SONGSETLISTPROVIDER_H
#define METABAND_SONGSETLISTPROVIDER_H

class UILabel;
class UIListLabel;

class SetlistProvider {
    void Text(int, int, UIListLabel*, UILabel*) const;
    void NumData() const;
};
#endif // METABAND_SONGSETLISTPROVIDER_H