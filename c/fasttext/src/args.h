/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#ifndef FASTTEXT_ARGS_H
#define FASTTEXT_ARGS_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace fasttext {

enum class model_name : int {cbow=1, sg, sup};  // 模型：非监督: cbow, skip-gram. 监督: sup
enum class loss_name : int {hs=1, ns, softmax};  // 损失函数

class Args {
  private:
    std::string lossToString(loss_name);

  public:
    Args();
    std::string input;
    std::string test;
    std::string output;
    double lr;
    int lrUpdateRate;
    int dim;
    int ws;
    int epoch;
    int minCount;
    int minCountLabel;
    int neg;
    int wordNgrams;  //  max length of word ngram 类似于词伙
    loss_name loss;
    model_name model;
    int bucket;
    int minn;  // min length of character ngrams 单词的子词
    int maxn;
    int thread;
    double t;
    std::string label;
    int verbose;
    std::string pretrainedVectors;
    int saveOutput;

    // 模型压缩的参数
    bool qout;  
    bool retrain;
    bool qnorm;
    size_t cutoff;
    size_t dsub;

    void parseArgs(const std::vector<std::string>& args);
    void printHelp();
    void printBasicHelp();
    void printDictionaryHelp();
    void printTrainingHelp();
    void printQuantizationHelp();
    void save(std::ostream&);
    void load(std::istream&);
};

}

#endif
