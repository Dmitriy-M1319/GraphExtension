#include "graph_types.h"
#include <iostream>
#include <algorithm>


std::vector<node> createNodes(const graph_egdes& eData, const graph_vertices& vData) {
    std::vector<node> result(vData.size());
    for(int i = 0; i < vData.size(); ++i) {
        auto val = std::find_if(eData.begin(), eData.end(),
            [&](const auto& e){ return e.first == vData[i] || e.second == vData[i]; });
        if(val != eData.end()) {
            result[i].nextEdgeId = std::distance(eData.begin(), val) + 1;
            // TODO: Сделать отдельные структуры нод и ребер, которые как раз таки будут использоваться для маппинга
            // с файлов
            result[i].data = vData[i];
        }
    }

    return result;
}

std::vector<edge> createEdges(const graph_egdes& eData, const graph_vertices& vData) {
    std::vector<edge> result(eData.size());
    auto rItt = result.begin();
    auto eItt = eData.begin();
    for(;rItt != result.end(); ++rItt, ++eItt) {
        auto firstVertex = std::find(vData.begin(), vData.end(), eItt->first);
        auto secondVertex = std::find(vData.begin(), vData.end(), eItt->second);
        (*rItt).firstNodeId = std::distance(vData.begin(), firstVertex) + 1;
        (*rItt).lastNodeId = std::distance(vData.begin(), secondVertex) + 1;

        auto revItt = std::make_reverse_iterator(eItt);
        auto prev = std::find_if(revItt, eData.rend(),
            [&](const auto& e){ return e.first == *firstVertex || e.second == *firstVertex; });
        if(prev != eData.rend()) {
            (*rItt).firstPrevEdge = std::distance(prev, eData.rend());
        }

        prev = std::find_if(revItt, eData.rend(),
            [&](const auto& e){ return e.first == *secondVertex || e.second == *secondVertex; });
        if(prev != eData.rend()) {
            (*rItt).lastPrevEdge = std::distance(prev, eData.rend());
        }

        auto last = std::find_if(eItt + 1, eData.end(),
            [&](const auto& e){ return e.first == *firstVertex || e.second == *firstVertex; });
        if(last != eData.end()) {
            (*rItt).firstNextEdge = std::distance(eData.begin(), last) + 1;
        }

        last = std::find_if(eItt + 1, eData.end(),
            [&](const auto& e){ return e.first == *secondVertex || e.second == *secondVertex; });
        if(last != eData.end()) {
            (*rItt).lastNextEdge = std::distance(eData.begin(), last) + 1;
        }
    }
    return result;
};


int main() {
    graph_vertices rawVData = { "A", "B", "C", "D", "E" };
    graph_egdes rawData = {
        {"A", "B"},
        {"A", "C"},
        {"B", "D"},
        {"B", "E"},
        {"B", "C"},
        {"C", "E"},
        {"D", "E"},
    };
    
    auto result = createNodes(rawData, rawVData);
    std::for_each(result.begin(), result.end(), [](const node& n) {
        std::cout << n.data << ": " << n.nextEdgeId <<  std::endl;
    });

    auto resultE = createEdges(rawData, rawVData);
    std::for_each(resultE.begin(), resultE.end(), [](const edge& n) {
        std::cout << n.firstNodeId << ": prev (" << n.firstPrevEdge << "), next (" << n.firstNextEdge << ") -> ";
        std::cout << n.lastNodeId << ": prev (" << n.lastPrevEdge << "), next (" << n.lastNextEdge << ")" << std::endl;
    });
    return 0;
}
