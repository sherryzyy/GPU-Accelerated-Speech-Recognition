#include <vector>
#include <map>
#include <set> 

#include "cuMatrix.h"
// #include "CTCNode.h"
#define DECODE_MAX_LEN 256
using namespace std;

struct BeamState
{
  float prob;
  int len;
  char path[DECODE_MAX_LEN];
};

class CTCBeamSearch 
{
    char* vocab; // vocab should include blank
    int beamWidth;
    int blankID;
    int vocabSize;
    // int decodeMaxLen;
    map<string, float> pathScore;
    set<string> path;

    // intermiate result
    map<string, float> updatePathScore;
    set<string> updatePath;

    map<string, float> finalPathScore;
    set<string> finalPath;

    // Sort the pointers, not the struct itself
    BeamState** beamStates;
    BeamState** nextBeamStates;

    BeamState* beamStateBuffer;
    BeamState* nextBeamStateBuffer;

    // char* pathBuffer; // vocabSize * beamWidth * decodeMaxLen
    // char* nextPathBuffer;

    // int* pathLens; // vocabSize * beamWidth
    // int* nextPathLens;

    // float* probs; // vocabSize * beamWidth
    // float* nextProbs;

    int* pathHashes; // vocabSize * beamWidth
    int numPaths;


public:
  // CTCBeamSearch(const vector<string> &vocab, int beamWidth, int blankID, int decodeMaxLen):vocab(vocab), beamWidth(beamWidth), blankID(blankID), decodeMaxLen(decodeMaxLen){
  //     vocabSize = vocab.size();

  //     cudaError_t error = cudaMalloc(&paths, beamWidth * vocabSize * sizeof(char*));
  //     error = cudaMalloc(&nextPaths, beamWidth * vocabSize * sizeof(char*));
  //     error = cudaMalloc(&probs, beamWidth * vocabSize * sizeof(float));
  //     error = cudaMalloc(&nextProbs, beamWidth * vocabSize * sizeof(float));
  //     error = cudaMalloc(&pathHashes, beamWidth * vocabSize * sizeof(int));
  //     if (error != cudaSuccess) {
  //       fprintf(stderr,"cudaError: %s\n", cudaGetErrorString(code));
  //     }
  // };

  CTCBeamSearch(char* vocab, int vocabSize, int beamWidth, int blankID):
    vocab(vocab), vocabSize(vocabSize), beamWidth(beamWidth), blankID(blankID) {
      this->vocab = new char[vocabSize];
      memcpy(this->vocab, vocab, vocabSize * sizeof(char));
      beamStates = NULL;
      nextBeamStates = NULL;
      beamStateBuffer = NULL;
      nextBeamStateBuffer = NULL;
      pathHashes = NULL;
  };

  void setup();


  string decode(cuMatrix<float>* seqProb); // assume prob is [seq,vocab] for now (no batch)
  void helper();

  void initialPath(float* prob); 
  void prune();
  void extend(float* prob);
  void mergeIdenticalPaths();

};