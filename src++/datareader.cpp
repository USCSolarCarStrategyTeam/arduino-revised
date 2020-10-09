#include <datareader.h>

std::string DataReader::getMostRecent() {
    strings recents = "";
    for (Source s : d_sources) {
        const Data d = s.getNewest();
        recents += SourceTypeLabels[s.getType()];
        recents += ": " + d.getValue() + "\n";
    }
    return recents;
}
