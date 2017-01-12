// Copyright 2017 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fuzzing_helpers.h"
#include "protobuf_mutator.h"

#include <google/protobuf/text_format.h>

using google::protobuf::Message;
using google::protobuf::TextFormat;

namespace protobuf_mutator {

void ParseTextMessage(const uint8_t* data, size_t size, Message* output) {
  output->Clear();
  TextFormat::Parser parser;
  parser.AllowPartialMessage(true);
  parser.ParseFromString({data, data + size}, output);
}

size_t MutateTextMessage(uint8_t* data, size_t size, size_t max_size,
                         ProtobufMutator* mutator, Message* prototype) {
  assert(size <= max_size);
  for (int i = 0; i < 100; ++i) {
    ParseTextMessage(data, size, prototype);
    mutator->Mutate(prototype, max_size - size);
    std::string result;
    if (TextFormat::PrintToString(*prototype, &result) &&
        result.size() <= max_size) {
      memcpy(data, result.data(), result.size());
      return result.size();
    }
  }

  return 0;
}

}  // namespace protobuf_mutator
