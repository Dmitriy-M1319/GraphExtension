#include "graph_types.h"
#include <iostream>
#include <algorithm>


std::vector<MemoryNode> createNodes(const GraphEgdes& eData, const GraphVertices& vData) {
    std::vector<MemoryNode> result(vData.size());
    for(int i = 0; i < vData.size(); ++i) {
        auto val = std::find_if(eData.begin(), eData.end(),
            [&](const auto& e){ return e.first == vData[i] || e.second == vData[i]; });
        if(val != eData.end()) {
            result[i].nextEdgeId = std::distance(eData.begin(), val) + 1;
            result[i].body = vData[i];
        }
    }

    return result;
}

std::vector<Edge> createEdges(const GraphEgdes& eData, const GraphVertices& vData) {
    std::vector<Edge> result(eData.size());
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
    KeyValue p1 = {"Key1", "Value1"};
    KeyValue p2 = {"Key2", "Value2"};
    KeyValue p3 = {"Key3", "Value3"};
    KeyValue p4 = {"Key4", "Value4"};
    KeyValue p5 = {"Key5", "Value5"};

    GraphVertices rawVData = {p1, p2, p3, p4, p5};
    GraphEgdes rawData = {
        {p1, p2},
        {p1, p3},
        {p2, p4},
        {p2, p5},
        {p2, p3},
        {p3, p5},
        {p4, p5},
    };
    
    auto result = createNodes(rawData, rawVData);
    std::for_each(result.begin(), result.end(), [](const MemoryNode& n) {
        std::cout << "{ " << n.body.first << " : " << n.body.second << " }" << ": " << n.nextEdgeId <<  std::endl;
    });

    auto resultE = createEdges(rawData, rawVData);
    std::for_each(resultE.begin(), resultE.end(), [](const Edge& n) {
        std::cout << n.firstNodeId << ": prev (" << n.firstPrevEdge << "), next (" << n.firstNextEdge << ") -> ";
        std::cout << n.lastNodeId << ": prev (" << n.lastPrevEdge << "), next (" << n.lastNextEdge << ")" << std::endl;
    });
    return 0;
}
