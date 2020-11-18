// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Demo.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Demo_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Demo_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3014000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3014000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Demo_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Demo_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Demo_2eproto;
class Reqest;
class ReqestDefaultTypeInternal;
extern ReqestDefaultTypeInternal _Reqest_default_instance_;
class Response;
class ResponseDefaultTypeInternal;
extern ResponseDefaultTypeInternal _Response_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::Reqest* Arena::CreateMaybeMessage<::Reqest>(Arena*);
template<> ::Response* Arena::CreateMaybeMessage<::Response>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class Reqest PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Reqest) */ {
 public:
  inline Reqest() : Reqest(nullptr) {}
  virtual ~Reqest();

  Reqest(const Reqest& from);
  Reqest(Reqest&& from) noexcept
    : Reqest() {
    *this = ::std::move(from);
  }

  inline Reqest& operator=(const Reqest& from) {
    CopyFrom(from);
    return *this;
  }
  inline Reqest& operator=(Reqest&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Reqest& default_instance();

  static inline const Reqest* internal_default_instance() {
    return reinterpret_cast<const Reqest*>(
               &_Reqest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Reqest& a, Reqest& b) {
    a.Swap(&b);
  }
  inline void Swap(Reqest* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Reqest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Reqest* New() const final {
    return CreateMaybeMessage<Reqest>(nullptr);
  }

  Reqest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Reqest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Reqest& from);
  void MergeFrom(const Reqest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Reqest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Reqest";
  }
  protected:
  explicit Reqest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Demo_2eproto);
    return ::descriptor_table_Demo_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMessageFieldNumber = 4,
    kSrcPlayerIdFieldNumber = 1,
    kDesPlayerIdFieldNumber = 2,
    kMessageTypeFieldNumber = 3,
  };
  // required string Message = 4;
  bool has_message() const;
  private:
  bool _internal_has_message() const;
  public:
  void clear_message();
  const std::string& message() const;
  void set_message(const std::string& value);
  void set_message(std::string&& value);
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  std::string* mutable_message();
  std::string* release_message();
  void set_allocated_message(std::string* message);
  private:
  const std::string& _internal_message() const;
  void _internal_set_message(const std::string& value);
  std::string* _internal_mutable_message();
  public:

  // required int32 SrcPlayerId = 1;
  bool has_srcplayerid() const;
  private:
  bool _internal_has_srcplayerid() const;
  public:
  void clear_srcplayerid();
  ::PROTOBUF_NAMESPACE_ID::int32 srcplayerid() const;
  void set_srcplayerid(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_srcplayerid() const;
  void _internal_set_srcplayerid(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // required int32 DesPlayerId = 2;
  bool has_desplayerid() const;
  private:
  bool _internal_has_desplayerid() const;
  public:
  void clear_desplayerid();
  ::PROTOBUF_NAMESPACE_ID::int32 desplayerid() const;
  void set_desplayerid(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_desplayerid() const;
  void _internal_set_desplayerid(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // required int32 MessageType = 3;
  bool has_messagetype() const;
  private:
  bool _internal_has_messagetype() const;
  public:
  void clear_messagetype();
  ::PROTOBUF_NAMESPACE_ID::int32 messagetype() const;
  void set_messagetype(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_messagetype() const;
  void _internal_set_messagetype(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:Reqest)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_;
  ::PROTOBUF_NAMESPACE_ID::int32 srcplayerid_;
  ::PROTOBUF_NAMESPACE_ID::int32 desplayerid_;
  ::PROTOBUF_NAMESPACE_ID::int32 messagetype_;
  friend struct ::TableStruct_Demo_2eproto;
};
// -------------------------------------------------------------------

class Response PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Response) */ {
 public:
  inline Response() : Response(nullptr) {}
  virtual ~Response();

  Response(const Response& from);
  Response(Response&& from) noexcept
    : Response() {
    *this = ::std::move(from);
  }

  inline Response& operator=(const Response& from) {
    CopyFrom(from);
    return *this;
  }
  inline Response& operator=(Response&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Response& default_instance();

  static inline const Response* internal_default_instance() {
    return reinterpret_cast<const Response*>(
               &_Response_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Response& a, Response& b) {
    a.Swap(&b);
  }
  inline void Swap(Response* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Response* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Response* New() const final {
    return CreateMaybeMessage<Response>(nullptr);
  }

  Response* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Response>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Response& from);
  void MergeFrom(const Response& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Response* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Response";
  }
  protected:
  explicit Response(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Demo_2eproto);
    return ::descriptor_table_Demo_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMessageFieldNumber = 2,
    kSrcPlayerIdFieldNumber = 1,
  };
  // required string Message = 2;
  bool has_message() const;
  private:
  bool _internal_has_message() const;
  public:
  void clear_message();
  const std::string& message() const;
  void set_message(const std::string& value);
  void set_message(std::string&& value);
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  std::string* mutable_message();
  std::string* release_message();
  void set_allocated_message(std::string* message);
  private:
  const std::string& _internal_message() const;
  void _internal_set_message(const std::string& value);
  std::string* _internal_mutable_message();
  public:

  // required int32 SrcPlayerId = 1;
  bool has_srcplayerid() const;
  private:
  bool _internal_has_srcplayerid() const;
  public:
  void clear_srcplayerid();
  ::PROTOBUF_NAMESPACE_ID::int32 srcplayerid() const;
  void set_srcplayerid(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_srcplayerid() const;
  void _internal_set_srcplayerid(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:Response)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_;
  ::PROTOBUF_NAMESPACE_ID::int32 srcplayerid_;
  friend struct ::TableStruct_Demo_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Reqest

// required int32 SrcPlayerId = 1;
inline bool Reqest::_internal_has_srcplayerid() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool Reqest::has_srcplayerid() const {
  return _internal_has_srcplayerid();
}
inline void Reqest::clear_srcplayerid() {
  srcplayerid_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Reqest::_internal_srcplayerid() const {
  return srcplayerid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Reqest::srcplayerid() const {
  // @@protoc_insertion_point(field_get:Reqest.SrcPlayerId)
  return _internal_srcplayerid();
}
inline void Reqest::_internal_set_srcplayerid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  srcplayerid_ = value;
}
inline void Reqest::set_srcplayerid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_srcplayerid(value);
  // @@protoc_insertion_point(field_set:Reqest.SrcPlayerId)
}

// required int32 DesPlayerId = 2;
inline bool Reqest::_internal_has_desplayerid() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool Reqest::has_desplayerid() const {
  return _internal_has_desplayerid();
}
inline void Reqest::clear_desplayerid() {
  desplayerid_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Reqest::_internal_desplayerid() const {
  return desplayerid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Reqest::desplayerid() const {
  // @@protoc_insertion_point(field_get:Reqest.DesPlayerId)
  return _internal_desplayerid();
}
inline void Reqest::_internal_set_desplayerid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000004u;
  desplayerid_ = value;
}
inline void Reqest::set_desplayerid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_desplayerid(value);
  // @@protoc_insertion_point(field_set:Reqest.DesPlayerId)
}

// required int32 MessageType = 3;
inline bool Reqest::_internal_has_messagetype() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool Reqest::has_messagetype() const {
  return _internal_has_messagetype();
}
inline void Reqest::clear_messagetype() {
  messagetype_ = 0;
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Reqest::_internal_messagetype() const {
  return messagetype_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Reqest::messagetype() const {
  // @@protoc_insertion_point(field_get:Reqest.MessageType)
  return _internal_messagetype();
}
inline void Reqest::_internal_set_messagetype(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000008u;
  messagetype_ = value;
}
inline void Reqest::set_messagetype(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_messagetype(value);
  // @@protoc_insertion_point(field_set:Reqest.MessageType)
}

// required string Message = 4;
inline bool Reqest::_internal_has_message() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool Reqest::has_message() const {
  return _internal_has_message();
}
inline void Reqest::clear_message() {
  message_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& Reqest::message() const {
  // @@protoc_insertion_point(field_get:Reqest.Message)
  return _internal_message();
}
inline void Reqest::set_message(const std::string& value) {
  _internal_set_message(value);
  // @@protoc_insertion_point(field_set:Reqest.Message)
}
inline std::string* Reqest::mutable_message() {
  // @@protoc_insertion_point(field_mutable:Reqest.Message)
  return _internal_mutable_message();
}
inline const std::string& Reqest::_internal_message() const {
  return message_.Get();
}
inline void Reqest::_internal_set_message(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void Reqest::set_message(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  message_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:Reqest.Message)
}
inline void Reqest::set_message(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:Reqest.Message)
}
inline void Reqest::set_message(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000001u;
  message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:Reqest.Message)
}
inline std::string* Reqest::_internal_mutable_message() {
  _has_bits_[0] |= 0x00000001u;
  return message_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* Reqest::release_message() {
  // @@protoc_insertion_point(field_release:Reqest.Message)
  if (!_internal_has_message()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return message_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Reqest::set_allocated_message(std::string* message) {
  if (message != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  message_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), message,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:Reqest.Message)
}

// -------------------------------------------------------------------

// Response

// required int32 SrcPlayerId = 1;
inline bool Response::_internal_has_srcplayerid() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool Response::has_srcplayerid() const {
  return _internal_has_srcplayerid();
}
inline void Response::clear_srcplayerid() {
  srcplayerid_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Response::_internal_srcplayerid() const {
  return srcplayerid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Response::srcplayerid() const {
  // @@protoc_insertion_point(field_get:Response.SrcPlayerId)
  return _internal_srcplayerid();
}
inline void Response::_internal_set_srcplayerid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  srcplayerid_ = value;
}
inline void Response::set_srcplayerid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_srcplayerid(value);
  // @@protoc_insertion_point(field_set:Response.SrcPlayerId)
}

// required string Message = 2;
inline bool Response::_internal_has_message() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool Response::has_message() const {
  return _internal_has_message();
}
inline void Response::clear_message() {
  message_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& Response::message() const {
  // @@protoc_insertion_point(field_get:Response.Message)
  return _internal_message();
}
inline void Response::set_message(const std::string& value) {
  _internal_set_message(value);
  // @@protoc_insertion_point(field_set:Response.Message)
}
inline std::string* Response::mutable_message() {
  // @@protoc_insertion_point(field_mutable:Response.Message)
  return _internal_mutable_message();
}
inline const std::string& Response::_internal_message() const {
  return message_.Get();
}
inline void Response::_internal_set_message(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void Response::set_message(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  message_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:Response.Message)
}
inline void Response::set_message(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:Response.Message)
}
inline void Response::set_message(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000001u;
  message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:Response.Message)
}
inline std::string* Response::_internal_mutable_message() {
  _has_bits_[0] |= 0x00000001u;
  return message_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* Response::release_message() {
  // @@protoc_insertion_point(field_release:Response.Message)
  if (!_internal_has_message()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return message_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Response::set_allocated_message(std::string* message) {
  if (message != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  message_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), message,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:Response.Message)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Demo_2eproto