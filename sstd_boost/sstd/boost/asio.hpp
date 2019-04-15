//
// asio.hpp
// ~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  See www.boost.org/libs/asio for documentation.
//

#ifndef BOOST_ASIO_HPP
#define BOOST_ASIO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <sstd/boost/asio/associated_allocator.hpp>
#include <sstd/boost/asio/associated_executor.hpp>
#include <sstd/boost/asio/async_result.hpp>
#include <sstd/boost/asio/basic_datagram_socket.hpp>
#include <sstd/boost/asio/basic_deadline_timer.hpp>
#include <sstd/boost/asio/basic_io_object.hpp>
#include <sstd/boost/asio/basic_raw_socket.hpp>
#include <sstd/boost/asio/basic_seq_packet_socket.hpp>
#include <sstd/boost/asio/basic_serial_port.hpp>
#include <sstd/boost/asio/basic_signal_set.hpp>
#include <sstd/boost/asio/basic_socket_acceptor.hpp>
#include <sstd/boost/asio/basic_socket_iostream.hpp>
#include <sstd/boost/asio/basic_socket_streambuf.hpp>
#include <sstd/boost/asio/basic_stream_socket.hpp>
#include <sstd/boost/asio/basic_streambuf.hpp>
#include <sstd/boost/asio/basic_waitable_timer.hpp>
#include <sstd/boost/asio/bind_executor.hpp>
#include <sstd/boost/asio/buffer.hpp>
#include <sstd/boost/asio/buffered_read_stream_fwd.hpp>
#include <sstd/boost/asio/buffered_read_stream.hpp>
#include <sstd/boost/asio/buffered_stream_fwd.hpp>
#include <sstd/boost/asio/buffered_stream.hpp>
#include <sstd/boost/asio/buffered_write_stream_fwd.hpp>
#include <sstd/boost/asio/buffered_write_stream.hpp>
#include <sstd/boost/asio/buffers_iterator.hpp>
#include <sstd/boost/asio/completion_condition.hpp>
#include <sstd/boost/asio/connect.hpp>
#include <sstd/boost/asio/coroutine.hpp>
#include <sstd/boost/asio/datagram_socket_service.hpp>
#include <sstd/boost/asio/deadline_timer_service.hpp>
#include <sstd/boost/asio/deadline_timer.hpp>
#include <sstd/boost/asio/defer.hpp>
#include <sstd/boost/asio/dispatch.hpp>
#include <sstd/boost/asio/error.hpp>
#include <sstd/boost/asio/execution_context.hpp>
#include <sstd/boost/asio/executor.hpp>
#include <sstd/boost/asio/executor_work_guard.hpp>
#include <sstd/boost/asio/generic/basic_endpoint.hpp>
#include <sstd/boost/asio/generic/datagram_protocol.hpp>
#include <sstd/boost/asio/generic/raw_protocol.hpp>
#include <sstd/boost/asio/generic/seq_packet_protocol.hpp>
#include <sstd/boost/asio/generic/stream_protocol.hpp>
#include <sstd/boost/asio/handler_alloc_hook.hpp>
#include <sstd/boost/asio/handler_continuation_hook.hpp>
#include <sstd/boost/asio/handler_invoke_hook.hpp>
#include <sstd/boost/asio/handler_type.hpp>
#include <sstd/boost/asio/high_resolution_timer.hpp>
#include <sstd/boost/asio/io_context.hpp>
#include <sstd/boost/asio/io_context_strand.hpp>
#include <sstd/boost/asio/io_service.hpp>
#include <sstd/boost/asio/io_service_strand.hpp>
#include <sstd/boost/asio/ip/address.hpp>
#include <sstd/boost/asio/ip/address_v4.hpp>
#include <sstd/boost/asio/ip/address_v4_iterator.hpp>
#include <sstd/boost/asio/ip/address_v4_range.hpp>
#include <sstd/boost/asio/ip/address_v6.hpp>
#include <sstd/boost/asio/ip/address_v6_iterator.hpp>
#include <sstd/boost/asio/ip/address_v6_range.hpp>
#include <sstd/boost/asio/ip/bad_address_cast.hpp>
#include <sstd/boost/asio/ip/basic_endpoint.hpp>
#include <sstd/boost/asio/ip/basic_resolver.hpp>
#include <sstd/boost/asio/ip/basic_resolver_entry.hpp>
#include <sstd/boost/asio/ip/basic_resolver_iterator.hpp>
#include <sstd/boost/asio/ip/basic_resolver_query.hpp>
#include <sstd/boost/asio/ip/host_name.hpp>
#include <sstd/boost/asio/ip/icmp.hpp>
#include <sstd/boost/asio/ip/multicast.hpp>
#include <sstd/boost/asio/ip/resolver_base.hpp>
#include <sstd/boost/asio/ip/resolver_query_base.hpp>
#include <sstd/boost/asio/ip/resolver_service.hpp>
#include <sstd/boost/asio/ip/tcp.hpp>
#include <sstd/boost/asio/ip/udp.hpp>
#include <sstd/boost/asio/ip/unicast.hpp>
#include <sstd/boost/asio/ip/v6_only.hpp>
#include <sstd/boost/asio/is_executor.hpp>
#include <sstd/boost/asio/is_read_buffered.hpp>
#include <sstd/boost/asio/is_write_buffered.hpp>
#include <sstd/boost/asio/local/basic_endpoint.hpp>
#include <sstd/boost/asio/local/connect_pair.hpp>
#include <sstd/boost/asio/local/datagram_protocol.hpp>
#include <sstd/boost/asio/local/stream_protocol.hpp>
#include <sstd/boost/asio/packaged_task.hpp>
#include <sstd/boost/asio/placeholders.hpp>
#include <sstd/boost/asio/posix/basic_descriptor.hpp>
#include <sstd/boost/asio/posix/basic_stream_descriptor.hpp>
#include <sstd/boost/asio/posix/descriptor.hpp>
#include <sstd/boost/asio/posix/descriptor_base.hpp>
#include <sstd/boost/asio/posix/stream_descriptor.hpp>
#include <sstd/boost/asio/posix/stream_descriptor_service.hpp>
#include <sstd/boost/asio/post.hpp>
#include <sstd/boost/asio/raw_socket_service.hpp>
#include <sstd/boost/asio/read.hpp>
#include <sstd/boost/asio/read_at.hpp>
#include <sstd/boost/asio/read_until.hpp>
#include <sstd/boost/asio/seq_packet_socket_service.hpp>
#include <sstd/boost/asio/serial_port.hpp>
#include <sstd/boost/asio/serial_port_base.hpp>
#include <sstd/boost/asio/serial_port_service.hpp>
#include <sstd/boost/asio/signal_set.hpp>
#include <sstd/boost/asio/signal_set_service.hpp>
#include <sstd/boost/asio/socket_acceptor_service.hpp>
#include <sstd/boost/asio/socket_base.hpp>
#include <sstd/boost/asio/steady_timer.hpp>
#include <sstd/boost/asio/strand.hpp>
#include <sstd/boost/asio/stream_socket_service.hpp>
#include <sstd/boost/asio/streambuf.hpp>
#include <sstd/boost/asio/system_context.hpp>
#include <sstd/boost/asio/system_executor.hpp>
#include <sstd/boost/asio/system_timer.hpp>
#include <sstd/boost/asio/thread_pool.hpp>
#include <sstd/boost/asio/time_traits.hpp>
#include <sstd/boost/asio/use_future.hpp>
#include <sstd/boost/asio/uses_executor.hpp>
#include <sstd/boost/asio/version.hpp>
#include <sstd/boost/asio/wait_traits.hpp>
#include <sstd/boost/asio/waitable_timer_service.hpp>
#include <sstd/boost/asio/windows/basic_handle.hpp>
#include <sstd/boost/asio/windows/basic_object_handle.hpp>
#include <sstd/boost/asio/windows/basic_random_access_handle.hpp>
#include <sstd/boost/asio/windows/basic_stream_handle.hpp>
#include <sstd/boost/asio/windows/object_handle.hpp>
#include <sstd/boost/asio/windows/object_handle_service.hpp>
#include <sstd/boost/asio/windows/overlapped_handle.hpp>
#include <sstd/boost/asio/windows/overlapped_ptr.hpp>
#include <sstd/boost/asio/windows/random_access_handle.hpp>
#include <sstd/boost/asio/windows/random_access_handle_service.hpp>
#include <sstd/boost/asio/windows/stream_handle.hpp>
#include <sstd/boost/asio/windows/stream_handle_service.hpp>
#include <sstd/boost/asio/write.hpp>
#include <sstd/boost/asio/write_at.hpp>

#endif // BOOST_ASIO_HPP
