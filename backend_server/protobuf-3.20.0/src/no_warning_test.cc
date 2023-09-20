// Generated from Makefile.am
#include <google/protobuf/any.h>
#include <google/protobuf/any.pb.h>
#include <google/protobuf/api.pb.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arena_impl.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/arenaz_sampler.h>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/command_line_interface.h>
#include <google/protobuf/compiler/cpp/cpp_file.h>
#include <google/protobuf/compiler/cpp/cpp_generator.h>
#include <google/protobuf/compiler/cpp/cpp_helpers.h>
#include <google/protobuf/compiler/cpp/cpp_names.h>
#include <google/protobuf/compiler/csharp/csharp_doc_comment.h>
#include <google/protobuf/compiler/csharp/csharp_generator.h>
#include <google/protobuf/compiler/csharp/csharp_names.h>
#include <google/protobuf/compiler/csharp/csharp_options.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/compiler/java/java_generator.h>
#include <google/protobuf/compiler/java/java_kotlin_generator.h>
#include <google/protobuf/compiler/java/java_names.h>
#include <google/protobuf/compiler/js/js_generator.h>
#include <google/protobuf/compiler/objectivec/objectivec_generator.h>
#include <google/protobuf/compiler/objectivec/objectivec_helpers.h>
#include <google/protobuf/compiler/parser.h>
#include <google/protobuf/compiler/php/php_generator.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/compiler/plugin.pb.h>
#include <google/protobuf/compiler/python/python_generator.h>
#include <google/protobuf/compiler/python/python_pyi_generator.h>
#include <google/protobuf/compiler/ruby/ruby_generator.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/descriptor_database.h>
#include <google/protobuf/duration.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/empty.pb.h>
#include <google/protobuf/explicitly_constructed.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/extension_set_inl.h>
#include <google/protobuf/field_access_listener.h>
#include <google/protobuf/field_mask.pb.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/generated_enum_util.h>
#include <google/protobuf/generated_message_bases.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/generated_message_tctable_decl.h>
#include <google/protobuf/generated_message_tctable_impl.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/has_bits.h>
#include <google/protobuf/implicit_weak_message.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/gzip_stream.h>
#include <google/protobuf/io/io_win32.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/strtod.h>
#include <google/protobuf/io/tokenizer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/map.h>
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_entry_lite.h>
#include <google/protobuf/map_field.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/map_field_lite.h>
#include <google/protobuf/map_type_handler.h>
#include <google/protobuf/message.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/parse_context.h>
#include <google/protobuf/port.h>
#include <google/protobuf/reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/repeated_ptr_field.h>
#include <google/protobuf/service.h>
#include <google/protobuf/source_context.pb.h>
#include <google/protobuf/struct.pb.h>
#include <google/protobuf/stubs/bytestream.h>
#include <google/protobuf/stubs/callback.h>
#include <google/protobuf/stubs/casts.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/hash.h>
#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/macros.h>
#include <google/protobuf/stubs/map_util.h>
#include <google/protobuf/stubs/mutex.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/stubs/platform_macros.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/status.h>
#include <google/protobuf/stubs/stl_util.h>
#include <google/protobuf/stubs/stringpiece.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/stubs/template_util.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/type.pb.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/util/delimited_message_util.h>
#include <google/protobuf/util/field_comparator.h>
#include <google/protobuf/util/field_mask_util.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/message_differencer.h>
#include <google/protobuf/util/time_util.h>
#include <google/protobuf/util/type_resolver.h>
#include <google/protobuf/util/type_resolver_util.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/wrappers.pb.h>
int main(int, char**) { return 0; }
