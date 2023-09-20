CC = g++
CXXFLAGS=-std=c++11 -pedantic -Wall -Werror -ggdb3 -lpthread -pthread
EXTRAFLAGS=`pkg-config --cflags --libs protobuf` -lpqxx -lpq
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS) world.pb.cc uta.pb.cc)
server:$(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS) $(EXTRAFLAGS)
.PHONY: clean depend
clean:
	rm -f server *.o *~ \#* *.bak
depend:
	makedepend $(SRCS)
# DO NOT DELETE

server.o: Communicator.hpp my_exception.hpp send_recv.hpp
server.o: /usr/include/google/protobuf/io/coded_stream.h
server.o: /usr/include/assert.h /usr/include/features.h
server.o: /usr/include/stdc-predef.h
server.o: /usr/include/google/protobuf/stubs/common.h
server.o: /usr/include/google/protobuf/stubs/port.h /usr/include/stdlib.h
server.o: /usr/include/alloca.h /usr/include/string.h /usr/include/strings.h
server.o: /usr/include/stdint.h
server.o: /usr/include/google/protobuf/stubs/platform_macros.h
server.o: /usr/include/byteswap.h /usr/include/google/protobuf/stubs/macros.h
server.o: /usr/include/google/protobuf/stubs/logging.h
server.o: /usr/include/google/protobuf/stubs/mutex.h
server.o: /usr/include/google/protobuf/stubs/callback.h
server.o: /usr/include/google/protobuf/io/zero_copy_stream_impl.h
server.o: /usr/include/google/protobuf/io/zero_copy_stream.h
server.o: /usr/include/google/protobuf/io/zero_copy_stream_impl_lite.h
server.o: /usr/include/google/protobuf/stubs/stl_util.h seqnum_cache.hpp
server.o: socket.hpp /usr/include/arpa/inet.h /usr/include/netinet/in.h
server.o: /usr/include/endian.h /usr/include/netdb.h /usr/include/rpc/netdb.h
server.o: /usr/include/unistd.h utils.hpp backend_logic.hpp dbConnect.hpp
server.o: /usr/include/pqxx/pqxx /usr/include/pqxx/array
server.o: /usr/include/pqxx/array.hxx /usr/include/pqxx/compiler-public.hxx
server.o: /usr/include/pqxx/config-public-compiler.h
server.o: /usr/include/pqxx/compiler-internal-pre.hxx
server.o: /usr/include/pqxx/internal/encoding_group.hxx
server.o: /usr/include/pqxx/internal/encodings.hxx
server.o: /usr/include/pqxx/compiler-internal-post.hxx
server.o: /usr/include/pqxx/binarystring /usr/include/pqxx/binarystring.hxx
server.o: /usr/include/pqxx/result.hxx /usr/include/pqxx/except.hxx
server.o: /usr/include/pqxx/util.hxx /usr/include/pqxx/strconv.hxx
server.o: /usr/include/pqxx/internal/libpq-forward.hxx
server.o: /usr/include/pqxx/types.hxx /usr/include/pqxx/connection
server.o: /usr/include/pqxx/connection.hxx
server.o: /usr/include/pqxx/connectionpolicy.hxx
server.o: /usr/include/pqxx/basic_connection.hxx
server.o: /usr/include/pqxx/connection_base.hxx
server.o: /usr/include/pqxx/errorhandler.hxx
server.o: /usr/include/pqxx/prepared_statement.hxx
server.o: /usr/include/pqxx/internal/statement_parameters.hxx
server.o: /usr/include/pqxx/strconv /usr/include/pqxx/util
server.o: /usr/include/pqxx/internal/type_utils.hxx
server.o: /usr/include/pqxx/version.hxx
server.o: /usr/include/pqxx/internal/ignore-deprecated-pre.hxx
server.o: /usr/include/pqxx/internal/ignore-deprecated-post.hxx
server.o: /usr/include/pqxx/cursor /usr/include/pqxx/cursor.hxx
server.o: /usr/include/pqxx/transaction_base.hxx
server.o: /usr/include/pqxx/isolation.hxx /usr/include/pqxx/row.hxx
server.o: /usr/include/pqxx/field.hxx
server.o: /usr/include/pqxx/internal/sql_cursor.hxx
server.o: /usr/include/pqxx/errorhandler /usr/include/pqxx/except
server.o: /usr/include/pqxx/largeobject /usr/include/pqxx/largeobject.hxx
server.o: /usr/include/pqxx/dbtransaction.hxx
server.o: /usr/include/pqxx/nontransaction
server.o: /usr/include/pqxx/nontransaction.hxx /usr/include/pqxx/notification
server.o: /usr/include/pqxx/notification.hxx /usr/include/pqxx/pipeline
server.o: /usr/include/pqxx/pipeline.hxx /usr/include/pqxx/prepared_statement
server.o: /usr/include/pqxx/result /usr/include/pqxx/result_iterator.hxx
server.o: /usr/include/pqxx/robusttransaction
server.o: /usr/include/pqxx/robusttransaction.hxx
server.o: /usr/include/pqxx/stream_from /usr/include/pqxx/stream_from.hxx
server.o: /usr/include/pqxx/stream_base.hxx /usr/include/pqxx/stream_to
server.o: /usr/include/pqxx/stream_to.hxx /usr/include/pqxx/subtransaction
server.o: /usr/include/pqxx/subtransaction.hxx /usr/include/pqxx/transaction
server.o: /usr/include/pqxx/transaction.hxx /usr/include/pqxx/transactor
server.o: /usr/include/pqxx/transactor.hxx gbp_message.hpp uta.pb.h
server.o: /usr/include/google/protobuf/arena.h
server.o: /usr/include/google/protobuf/arena_impl.h
server.o: /usr/include/google/protobuf/arenastring.h
server.o: /usr/include/google/protobuf/stubs/fastmem.h /usr/include/stdio.h
server.o: /usr/include/google/protobuf/generated_message_util.h
server.o: /usr/include/google/protobuf/stubs/once.h
server.o: /usr/include/google/protobuf/has_bits.h
server.o: /usr/include/google/protobuf/implicit_weak_message.h
server.o: /usr/include/google/protobuf/message_lite.h
server.o: /usr/include/google/protobuf/map_entry_lite.h
server.o: /usr/include/google/protobuf/stubs/casts.h
server.o: /usr/include/google/protobuf/map.h
server.o: /usr/include/google/protobuf/generated_enum_util.h
server.o: /usr/include/google/protobuf/map_type_handler.h
server.o: /usr/include/google/protobuf/wire_format_lite_inl.h
server.o: /usr/include/google/protobuf/repeated_field.h
server.o: /usr/include/google/protobuf/wire_format_lite.h
server.o: /usr/include/google/protobuf/stubs/hash.h
server.o: /usr/include/google/protobuf/metadata_lite.h
server.o: /usr/include/google/protobuf/generated_message_reflection.h
server.o: /usr/include/google/protobuf/generated_enum_reflection.h
server.o: /usr/include/google/protobuf/message.h
server.o: /usr/include/google/protobuf/descriptor.h
server.o: /usr/include/google/protobuf/metadata.h
server.o: /usr/include/google/protobuf/unknown_field_set.h
server.o: /usr/include/google/protobuf/extension_set.h world.pb.h json.hpp
dbConnect.o: dbConnect.hpp /usr/include/pqxx/pqxx /usr/include/pqxx/array
dbConnect.o: /usr/include/pqxx/array.hxx
dbConnect.o: /usr/include/pqxx/compiler-public.hxx
dbConnect.o: /usr/include/pqxx/config-public-compiler.h
dbConnect.o: /usr/include/pqxx/compiler-internal-pre.hxx
dbConnect.o: /usr/include/pqxx/internal/encoding_group.hxx
dbConnect.o: /usr/include/pqxx/internal/encodings.hxx
dbConnect.o: /usr/include/pqxx/compiler-internal-post.hxx
dbConnect.o: /usr/include/pqxx/binarystring
dbConnect.o: /usr/include/pqxx/binarystring.hxx /usr/include/pqxx/result.hxx
dbConnect.o: /usr/include/pqxx/except.hxx /usr/include/pqxx/util.hxx
dbConnect.o: /usr/include/pqxx/strconv.hxx
dbConnect.o: /usr/include/pqxx/internal/libpq-forward.hxx
dbConnect.o: /usr/include/pqxx/types.hxx /usr/include/pqxx/connection
dbConnect.o: /usr/include/pqxx/connection.hxx
dbConnect.o: /usr/include/pqxx/connectionpolicy.hxx
dbConnect.o: /usr/include/pqxx/basic_connection.hxx
dbConnect.o: /usr/include/pqxx/connection_base.hxx
dbConnect.o: /usr/include/pqxx/errorhandler.hxx
dbConnect.o: /usr/include/pqxx/prepared_statement.hxx
dbConnect.o: /usr/include/pqxx/internal/statement_parameters.hxx
dbConnect.o: /usr/include/pqxx/strconv /usr/include/pqxx/util
dbConnect.o: /usr/include/pqxx/internal/type_utils.hxx
dbConnect.o: /usr/include/pqxx/version.hxx
dbConnect.o: /usr/include/pqxx/internal/ignore-deprecated-pre.hxx
dbConnect.o: /usr/include/pqxx/internal/ignore-deprecated-post.hxx
dbConnect.o: /usr/include/pqxx/cursor /usr/include/pqxx/cursor.hxx
dbConnect.o: /usr/include/pqxx/transaction_base.hxx
dbConnect.o: /usr/include/pqxx/isolation.hxx /usr/include/pqxx/row.hxx
dbConnect.o: /usr/include/pqxx/field.hxx
dbConnect.o: /usr/include/pqxx/internal/sql_cursor.hxx
dbConnect.o: /usr/include/pqxx/errorhandler /usr/include/pqxx/except
dbConnect.o: /usr/include/pqxx/largeobject /usr/include/pqxx/largeobject.hxx
dbConnect.o: /usr/include/pqxx/dbtransaction.hxx
dbConnect.o: /usr/include/pqxx/nontransaction
dbConnect.o: /usr/include/pqxx/nontransaction.hxx
dbConnect.o: /usr/include/pqxx/notification
dbConnect.o: /usr/include/pqxx/notification.hxx /usr/include/pqxx/pipeline
dbConnect.o: /usr/include/pqxx/pipeline.hxx
dbConnect.o: /usr/include/pqxx/prepared_statement /usr/include/pqxx/result
dbConnect.o: /usr/include/pqxx/result_iterator.hxx
dbConnect.o: /usr/include/pqxx/robusttransaction
dbConnect.o: /usr/include/pqxx/robusttransaction.hxx
dbConnect.o: /usr/include/pqxx/stream_from /usr/include/pqxx/stream_from.hxx
dbConnect.o: /usr/include/pqxx/stream_base.hxx /usr/include/pqxx/stream_to
dbConnect.o: /usr/include/pqxx/stream_to.hxx /usr/include/pqxx/subtransaction
dbConnect.o: /usr/include/pqxx/subtransaction.hxx
dbConnect.o: /usr/include/pqxx/transaction /usr/include/pqxx/transaction.hxx
dbConnect.o: /usr/include/pqxx/transactor /usr/include/pqxx/transactor.hxx
utils.o: utils.hpp
socket.o: socket.hpp /usr/include/arpa/inet.h /usr/include/features.h
socket.o: /usr/include/stdc-predef.h /usr/include/netinet/in.h
socket.o: /usr/include/endian.h /usr/include/netdb.h /usr/include/rpc/netdb.h
socket.o: /usr/include/unistd.h
gbp_message.o: gbp_message.hpp uta.pb.h
gbp_message.o: /usr/include/google/protobuf/io/coded_stream.h
gbp_message.o: /usr/include/assert.h /usr/include/features.h
gbp_message.o: /usr/include/stdc-predef.h
gbp_message.o: /usr/include/google/protobuf/stubs/common.h
gbp_message.o: /usr/include/google/protobuf/stubs/port.h
gbp_message.o: /usr/include/stdlib.h /usr/include/alloca.h
gbp_message.o: /usr/include/string.h /usr/include/strings.h
gbp_message.o: /usr/include/stdint.h
gbp_message.o: /usr/include/google/protobuf/stubs/platform_macros.h
gbp_message.o: /usr/include/byteswap.h
gbp_message.o: /usr/include/google/protobuf/stubs/macros.h
gbp_message.o: /usr/include/google/protobuf/stubs/logging.h
gbp_message.o: /usr/include/google/protobuf/stubs/mutex.h
gbp_message.o: /usr/include/google/protobuf/stubs/callback.h
gbp_message.o: /usr/include/google/protobuf/arena.h
gbp_message.o: /usr/include/google/protobuf/arena_impl.h
gbp_message.o: /usr/include/google/protobuf/arenastring.h
gbp_message.o: /usr/include/google/protobuf/stubs/fastmem.h
gbp_message.o: /usr/include/stdio.h
gbp_message.o: /usr/include/google/protobuf/generated_message_util.h
gbp_message.o: /usr/include/google/protobuf/stubs/once.h
gbp_message.o: /usr/include/google/protobuf/has_bits.h
gbp_message.o: /usr/include/google/protobuf/implicit_weak_message.h
gbp_message.o: /usr/include/google/protobuf/message_lite.h
gbp_message.o: /usr/include/google/protobuf/map_entry_lite.h
gbp_message.o: /usr/include/google/protobuf/stubs/casts.h
gbp_message.o: /usr/include/google/protobuf/map.h
gbp_message.o: /usr/include/google/protobuf/generated_enum_util.h
gbp_message.o: /usr/include/google/protobuf/map_type_handler.h
gbp_message.o: /usr/include/google/protobuf/wire_format_lite_inl.h
gbp_message.o: /usr/include/google/protobuf/repeated_field.h
gbp_message.o: /usr/include/google/protobuf/wire_format_lite.h
gbp_message.o: /usr/include/google/protobuf/stubs/hash.h
gbp_message.o: /usr/include/google/protobuf/metadata_lite.h
gbp_message.o: /usr/include/google/protobuf/generated_message_reflection.h
gbp_message.o: /usr/include/google/protobuf/generated_enum_reflection.h
gbp_message.o: /usr/include/google/protobuf/message.h
gbp_message.o: /usr/include/google/protobuf/descriptor.h
gbp_message.o: /usr/include/google/protobuf/metadata.h
gbp_message.o: /usr/include/google/protobuf/unknown_field_set.h
gbp_message.o: /usr/include/google/protobuf/extension_set.h utils.hpp
gbp_message.o: world.pb.h
backend_logic.o: backend_logic.hpp Communicator.hpp my_exception.hpp
backend_logic.o: send_recv.hpp /usr/include/google/protobuf/io/coded_stream.h
backend_logic.o: /usr/include/assert.h /usr/include/features.h
backend_logic.o: /usr/include/stdc-predef.h
backend_logic.o: /usr/include/google/protobuf/stubs/common.h
backend_logic.o: /usr/include/google/protobuf/stubs/port.h
backend_logic.o: /usr/include/stdlib.h /usr/include/alloca.h
backend_logic.o: /usr/include/string.h /usr/include/strings.h
backend_logic.o: /usr/include/stdint.h
backend_logic.o: /usr/include/google/protobuf/stubs/platform_macros.h
backend_logic.o: /usr/include/byteswap.h
backend_logic.o: /usr/include/google/protobuf/stubs/macros.h
backend_logic.o: /usr/include/google/protobuf/stubs/logging.h
backend_logic.o: /usr/include/google/protobuf/stubs/mutex.h
backend_logic.o: /usr/include/google/protobuf/stubs/callback.h
backend_logic.o: /usr/include/google/protobuf/io/zero_copy_stream_impl.h
backend_logic.o: /usr/include/google/protobuf/io/zero_copy_stream.h
backend_logic.o: /usr/include/google/protobuf/io/zero_copy_stream_impl_lite.h
backend_logic.o: /usr/include/google/protobuf/stubs/stl_util.h
backend_logic.o: seqnum_cache.hpp socket.hpp /usr/include/arpa/inet.h
backend_logic.o: /usr/include/netinet/in.h /usr/include/endian.h
backend_logic.o: /usr/include/netdb.h /usr/include/rpc/netdb.h
backend_logic.o: /usr/include/unistd.h utils.hpp dbConnect.hpp
backend_logic.o: /usr/include/pqxx/pqxx /usr/include/pqxx/array
backend_logic.o: /usr/include/pqxx/array.hxx
backend_logic.o: /usr/include/pqxx/compiler-public.hxx
backend_logic.o: /usr/include/pqxx/config-public-compiler.h
backend_logic.o: /usr/include/pqxx/compiler-internal-pre.hxx
backend_logic.o: /usr/include/pqxx/internal/encoding_group.hxx
backend_logic.o: /usr/include/pqxx/internal/encodings.hxx
backend_logic.o: /usr/include/pqxx/compiler-internal-post.hxx
backend_logic.o: /usr/include/pqxx/binarystring
backend_logic.o: /usr/include/pqxx/binarystring.hxx
backend_logic.o: /usr/include/pqxx/result.hxx /usr/include/pqxx/except.hxx
backend_logic.o: /usr/include/pqxx/util.hxx /usr/include/pqxx/strconv.hxx
backend_logic.o: /usr/include/pqxx/internal/libpq-forward.hxx
backend_logic.o: /usr/include/pqxx/types.hxx /usr/include/pqxx/connection
backend_logic.o: /usr/include/pqxx/connection.hxx
backend_logic.o: /usr/include/pqxx/connectionpolicy.hxx
backend_logic.o: /usr/include/pqxx/basic_connection.hxx
backend_logic.o: /usr/include/pqxx/connection_base.hxx
backend_logic.o: /usr/include/pqxx/errorhandler.hxx
backend_logic.o: /usr/include/pqxx/prepared_statement.hxx
backend_logic.o: /usr/include/pqxx/internal/statement_parameters.hxx
backend_logic.o: /usr/include/pqxx/strconv /usr/include/pqxx/util
backend_logic.o: /usr/include/pqxx/internal/type_utils.hxx
backend_logic.o: /usr/include/pqxx/version.hxx
backend_logic.o: /usr/include/pqxx/internal/ignore-deprecated-pre.hxx
backend_logic.o: /usr/include/pqxx/internal/ignore-deprecated-post.hxx
backend_logic.o: /usr/include/pqxx/cursor /usr/include/pqxx/cursor.hxx
backend_logic.o: /usr/include/pqxx/transaction_base.hxx
backend_logic.o: /usr/include/pqxx/isolation.hxx /usr/include/pqxx/row.hxx
backend_logic.o: /usr/include/pqxx/field.hxx
backend_logic.o: /usr/include/pqxx/internal/sql_cursor.hxx
backend_logic.o: /usr/include/pqxx/errorhandler /usr/include/pqxx/except
backend_logic.o: /usr/include/pqxx/largeobject
backend_logic.o: /usr/include/pqxx/largeobject.hxx
backend_logic.o: /usr/include/pqxx/dbtransaction.hxx
backend_logic.o: /usr/include/pqxx/nontransaction
backend_logic.o: /usr/include/pqxx/nontransaction.hxx
backend_logic.o: /usr/include/pqxx/notification
backend_logic.o: /usr/include/pqxx/notification.hxx
backend_logic.o: /usr/include/pqxx/pipeline /usr/include/pqxx/pipeline.hxx
backend_logic.o: /usr/include/pqxx/prepared_statement
backend_logic.o: /usr/include/pqxx/result
backend_logic.o: /usr/include/pqxx/result_iterator.hxx
backend_logic.o: /usr/include/pqxx/robusttransaction
backend_logic.o: /usr/include/pqxx/robusttransaction.hxx
backend_logic.o: /usr/include/pqxx/stream_from
backend_logic.o: /usr/include/pqxx/stream_from.hxx
backend_logic.o: /usr/include/pqxx/stream_base.hxx
backend_logic.o: /usr/include/pqxx/stream_to /usr/include/pqxx/stream_to.hxx
backend_logic.o: /usr/include/pqxx/subtransaction
backend_logic.o: /usr/include/pqxx/subtransaction.hxx
backend_logic.o: /usr/include/pqxx/transaction
backend_logic.o: /usr/include/pqxx/transaction.hxx
backend_logic.o: /usr/include/pqxx/transactor
backend_logic.o: /usr/include/pqxx/transactor.hxx gbp_message.hpp uta.pb.h
backend_logic.o: /usr/include/google/protobuf/arena.h
backend_logic.o: /usr/include/google/protobuf/arena_impl.h
backend_logic.o: /usr/include/google/protobuf/arenastring.h
backend_logic.o: /usr/include/google/protobuf/stubs/fastmem.h
backend_logic.o: /usr/include/stdio.h
backend_logic.o: /usr/include/google/protobuf/generated_message_util.h
backend_logic.o: /usr/include/google/protobuf/stubs/once.h
backend_logic.o: /usr/include/google/protobuf/has_bits.h
backend_logic.o: /usr/include/google/protobuf/implicit_weak_message.h
backend_logic.o: /usr/include/google/protobuf/message_lite.h
backend_logic.o: /usr/include/google/protobuf/map_entry_lite.h
backend_logic.o: /usr/include/google/protobuf/stubs/casts.h
backend_logic.o: /usr/include/google/protobuf/map.h
backend_logic.o: /usr/include/google/protobuf/generated_enum_util.h
backend_logic.o: /usr/include/google/protobuf/map_type_handler.h
backend_logic.o: /usr/include/google/protobuf/wire_format_lite_inl.h
backend_logic.o: /usr/include/google/protobuf/repeated_field.h
backend_logic.o: /usr/include/google/protobuf/wire_format_lite.h
backend_logic.o: /usr/include/google/protobuf/stubs/hash.h
backend_logic.o: /usr/include/google/protobuf/metadata_lite.h
backend_logic.o: /usr/include/google/protobuf/generated_message_reflection.h
backend_logic.o: /usr/include/google/protobuf/generated_enum_reflection.h
backend_logic.o: /usr/include/google/protobuf/message.h
backend_logic.o: /usr/include/google/protobuf/descriptor.h
backend_logic.o: /usr/include/google/protobuf/metadata.h
backend_logic.o: /usr/include/google/protobuf/unknown_field_set.h
backend_logic.o: /usr/include/google/protobuf/extension_set.h world.pb.h
backend_logic.o: json.hpp
