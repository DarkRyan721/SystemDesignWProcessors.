#ifndef SRC_NODE_BUILTINS_H_
#define SRC_NODE_BUILTINS_H_

#if defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#include <list>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>
#include "node_external_reference.h"
#include "node_mutex.h"
#include "node_threadsafe_cow.h"
#include "node_union_bytes.h"
#include "v8.h"

// Forward declare test fixture for `friend` declaration.
class PerProcessTest;

namespace node {
class SnapshotBuilder;
class ExternalReferenceRegistry;
class Realm;

namespace builtins {

class BuiltinCodeCacheData {
 public:
  BuiltinCodeCacheData() : data(nullptr), length(0), owning_ptr(nullptr) {}

  explicit BuiltinCodeCacheData(
      std::shared_ptr<v8::ScriptCompiler::CachedData> cached_data)
      : data(cached_data->data),
        length(cached_data->length),
        owning_ptr(cached_data) {}

  explicit BuiltinCodeCacheData(
      std::shared_ptr<std::vector<uint8_t>> cached_data)
      : data(cached_data->data()),
        length(cached_data->size()),
        owning_ptr(cached_data) {}

  BuiltinCodeCacheData(const uint8_t* data, size_t length)
      : data(data), length(length), owning_ptr(nullptr) {}

  const uint8_t* data;
  size_t length;

  // Returns a v8::ScriptCompiler::CachedData corresponding to this
  // BuiltinCodeCacheData. The lifetime of the returned
  // v8::ScriptCompiler::CachedData must not outlive that of the data.
  std::unique_ptr<v8::ScriptCompiler::CachedData> AsCachedData() {
    return std::make_unique<v8::ScriptCompiler::CachedData>(
        data, length, v8::ScriptCompiler::CachedData::BufferNotOwned);
  }

 private:
  // If not null, represents a pointer which owns data. Otherwise indicates
  // that data has static lifetime.
  std::shared_ptr<void> owning_ptr;
};

struct CodeCacheInfo {
  std::string id;
  BuiltinCodeCacheData data;
};

using BuiltinSourceMap = std::map<std::string, UnionBytes>;
using BuiltinCodeCacheMap =
    std::unordered_map<std::string, BuiltinCodeCacheData>;

// Generated by tools/js2c.py as node_javascript.cc
void RegisterExternalReferencesForInternalizedBuiltinCode(
    ExternalReferenceRegistry* registry);

// Handles compilation and caching of built-in JavaScript modules and
// bootstrap scripts, whose source are bundled into the binary as static data.
class NODE_EXTERN_PRIVATE BuiltinLoader {
 public:
  BuiltinLoader();
  BuiltinLoader(const BuiltinLoader&) = delete;
  BuiltinLoader& operator=(const BuiltinLoader&) = delete;

  static void RegisterExternalReferences(ExternalReferenceRegistry* registry);
  static void CreatePerIsolateProperties(IsolateData* isolate_data,
                                         v8::Local<v8::ObjectTemplate> target);
  static void CreatePerContextProperties(v8::Local<v8::Object> target,
                                         v8::Local<v8::Value> unused,
                                         v8::Local<v8::Context> context,
                                         void* priv);

  // The parameters used to compile the scripts are detected based on
  // the pattern of the id.
  v8::MaybeLocal<v8::Function> LookupAndCompile(v8::Local<v8::Context> context,
                                                const char* id,
                                                Realm* optional_realm);

  v8::MaybeLocal<v8::Value> CompileAndCall(v8::Local<v8::Context> context,
                                           const char* id,
                                           int argc,
                                           v8::Local<v8::Value> argv[],
                                           Realm* optional_realm);

  v8::MaybeLocal<v8::Value> CompileAndCall(v8::Local<v8::Context> context,
                                           const char* id,
                                           Realm* realm);

  // Returns config.gypi as a JSON string
  v8::Local<v8::String> GetConfigString(v8::Isolate* isolate);
  bool Exists(const char* id);
  bool Add(const char* id, const UnionBytes& source);

  bool CompileAllBuiltins(v8::Local<v8::Context> context);
  void RefreshCodeCache(const std::vector<CodeCacheInfo>& in);
  void CopyCodeCache(std::vector<CodeCacheInfo>* out) const;

  void CopySourceAndCodeCacheReferenceFrom(const BuiltinLoader* other);

 private:
  // Only allow access from friends.
  friend class CodeCacheBuilder;

  // Generated by tools/js2c.py as node_javascript.cc
  void LoadJavaScriptSource();  // Loads data into source_
  UnionBytes GetConfig();       // Return data for config.gypi

  std::vector<std::string_view> GetBuiltinIds() const;

  struct BuiltinCategories {
    std::set<std::string> can_be_required;
    std::set<std::string> cannot_be_required;
  };
  // This method builds `BuiltinCategories` from scratch every time,
  // and is therefore somewhat expensive, but also currently only being
  // used for testing, so that should not be an issue.
  BuiltinCategories GetBuiltinCategories() const;

  const v8::ScriptCompiler::CachedData* GetCodeCache(const char* id) const;
  enum class Result { kWithCache, kWithoutCache };
  v8::MaybeLocal<v8::String> LoadBuiltinSource(v8::Isolate* isolate,
                                               const char* id) const;
  // If an exception is encountered (e.g. source code contains
  // syntax error), the returned value is empty.
  v8::MaybeLocal<v8::Function> LookupAndCompileInternal(
      v8::Local<v8::Context> context,
      const char* id,
      std::vector<v8::Local<v8::String>>* parameters,
      Realm* optional_realm);
  void SaveCodeCache(const char* id, v8::Local<v8::Function> fn);

  static void RecordResult(const char* id,
                           BuiltinLoader::Result result,
                           Realm* realm);
  static void GetBuiltinCategories(
      v8::Local<v8::Name> property,
      const v8::PropertyCallbackInfo<v8::Value>& info);
  static void GetCacheUsage(const v8::FunctionCallbackInfo<v8::Value>& args);
  // Passing ids of built-in source code into JS land as
  // internalBinding('builtins').builtinIds
  static void BuiltinIdsGetter(v8::Local<v8::Name> property,
                               const v8::PropertyCallbackInfo<v8::Value>& info);
  // Passing config.gypi into JS land as internalBinding('builtins').config
  static void ConfigStringGetter(
      v8::Local<v8::Name> property,
      const v8::PropertyCallbackInfo<v8::Value>& info);
  // Compile a specific built-in as a function
  static void CompileFunction(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void HasCachedBuiltins(
      const v8::FunctionCallbackInfo<v8::Value>& args);
  // For legacy process.binding('natives')
  static void GetNatives(v8::Local<v8::Name> property,
                         const v8::PropertyCallbackInfo<v8::Value>& info);

  void AddExternalizedBuiltin(const char* id, const char* filename);

  ThreadsafeCopyOnWrite<BuiltinSourceMap> source_;

  const UnionBytes config_;

  struct BuiltinCodeCache {
    RwLock mutex;
    BuiltinCodeCacheMap map;
    bool has_code_cache = false;
  };
  std::shared_ptr<BuiltinCodeCache> code_cache_;

  friend class ::PerProcessTest;
};
}  // namespace builtins

}  // namespace node

#endif  // defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#endif  // SRC_NODE_BUILTINS_H_
