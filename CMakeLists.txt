
cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_SOURCE_DIR}/main.cmake)

if(NOT DEFINED PROJECT_NAME)
	set(PROJECT_NAME w600)
endif()

#设置编译工具链及选项
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/option.cmake)

project(${PROJECT_NAME} C CXX ASM)

#设置SDK所在目录
set(SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/WM_SDK_60X)

#设置链接脚本
option(BUILD_FLASH_2M "2m flash" OFF)

if(${BUILD_FLASH_2M})
	set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS} \
		-T${SDK_ROOT}/Tools/GNU/link_w600_2m.ld \
        -Wl,-Map,${PROJECT_NAME}.map \
		-Wl,-warn-common " )
else()
	set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS} \
		-T${SDK_ROOT}/Tools/GNU/link_w600_1m.ld \
		-Wl,-Map,${PROJECT_NAME}.map \
		-Wl,-warn-common " )
endif()


#SDK头文件
list(APPEND SDK_INCLUDE_DIRS
${SDK_ROOT}/Include/
${SDK_ROOT}/Src/OS/uCOS-II/ports/
${SDK_ROOT}/Src/OS/uCOS-II/source/
${SDK_ROOT}/Src/OS/uCOS-II/
${SDK_ROOT}/Src/OS/RTOS/include/
${SDK_ROOT}/Src/Wlan/Driver/
${SDK_ROOT}/Src/Wlan/Supplicant/
${SDK_ROOT}/Platform/Common/Params/
${SDK_ROOT}/Platform/Common/task/
${SDK_ROOT}/Platform/Common/mem/
${SDK_ROOT}/Platform/Common/fwup/
${SDK_ROOT}/Platform/Common/utils/
${SDK_ROOT}/Platform/Common/crypto/
${SDK_ROOT}/Platform/Common/crypto/symmetric/
${SDK_ROOT}/Platform/Common/crypto/digest/
${SDK_ROOT}/Platform/Common/crypto/math/
${SDK_ROOT}/Platform/Inc/
${SDK_ROOT}/Platform/Sys/
${SDK_ROOT}/Src/App/wm_atcmd/
${SDK_ROOT}/Src/App/matrixssl/
${SDK_ROOT}/Src/App/matrixssl/core/
${SDK_ROOT}/Src/App/libupnp-1.6.19/ixml/inc/
${SDK_ROOT}/Src/App/libupnp-1.6.19/upnp/inc/
${SDK_ROOT}/Src/App/libupnp-1.6.19/ixml/include/
${SDK_ROOT}/Src/App/libupnp-1.6.19/threadutil/include/
${SDK_ROOT}/Src/App/libupnp-1.6.19/upnp/include/
${SDK_ROOT}/Src/App/gmediarender-0.0.6/
${SDK_ROOT}/Src/App/web/
${SDK_ROOT}/Src/App/OTA/
${SDK_ROOT}/Src/App/cloud/
${SDK_ROOT}/Src/App/cJSON/
${SDK_ROOT}/Src/App/ajtcl-15.04.00a/inc/
${SDK_ROOT}/Src/App/ajtcl-15.04.00a/target/winnermicro/
${SDK_ROOT}/Src/App/ajtcl-15.04.00a/external/sha2/
${SDK_ROOT}/Src/App/cJSON/
${SDK_ROOT}/Src/App/cloud/
${SDK_ROOT}/Src/App/oneshotconfig/
${SDK_ROOT}/Src/App/dhcpserver/
${SDK_ROOT}/Src/App/dnsserver/
${SDK_ROOT}/Src/App/ping/
${SDK_ROOT}/Src/App/iperf/
${SDK_ROOT}/Src/App/libcoap/include/
${SDK_ROOT}/Src/App/polarssl/include/
${SDK_ROOT}/Src/App/mDNS/mDNSCore/
${SDK_ROOT}/Src/App/mDNS/mDNSPosix/
${SDK_ROOT}/Src/App/mqtt/
${SDK_ROOT}/Src/App/easylogger/inc/
${SDK_ROOT}/Demo/
${SDK_ROOT}/Include/App/
${SDK_ROOT}/Include/Net/
${SDK_ROOT}/Include/WiFi/
${SDK_ROOT}/Include/OS/
${SDK_ROOT}/Include/Driver/
${SDK_ROOT}/Include/Platform/
${SDK_ROOT}/Platform/Drivers/litepoint/
${SDK_ROOT}/Src/App/demo/
${SDK_ROOT}/Platform/Boot/gcc/
${SDK_ROOT}/Src/Network/api2.0.3/
${SDK_ROOT}/Src/Network/lwip2.0.3/
${SDK_ROOT}/Src/Network/lwip2.0.3/include/
${SDK_ROOT}/Src/Network/lwip2.0.3/include/arch/
${SDK_ROOT}/Src/Network/lwip2.0.3/include/lwip/
${SDK_ROOT}/Src/Network/lwip2.0.3/include/netif/
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/
${SDK_ROOT}/Src/App/httpclient/
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/er-coap-13/
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/shared/
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/
)

list(APPEND SDK_SRCS

#demo
${SDK_ROOT}/Demo/wm_crypt_demo.c
${SDK_ROOT}/Demo/wm_apsta_demo.c
${SDK_ROOT}/Demo/wm_mcast_demo.c
${SDK_ROOT}/Demo/wm_socket_client_demo.c
${SDK_ROOT}/Demo/wm_socket_fwup_demo.c
${SDK_ROOT}/Demo/wm_socket_server_demo.c
${SDK_ROOT}/Demo/wm_softap_demo.c
${SDK_ROOT}/Demo/wm_udp_demo.c
${SDK_ROOT}/Demo/wm_i2c_demo.c
${SDK_ROOT}/Demo/wm_i2s_demo.c
${SDK_ROOT}/Demo/wm_adc_demo.c
${SDK_ROOT}/Demo/wm_7816_demo.c
${SDK_ROOT}/Demo/wm_uart_demo.c
${SDK_ROOT}/Demo/console/wm_demo_console_task.c
${SDK_ROOT}/Demo/wm_gpio_demo.c
${SDK_ROOT}/Demo/wm_flash_demo.c
${SDK_ROOT}/Demo/wm_pwm_demo.c
${SDK_ROOT}/Demo/wm_slave_spi_demo.c
${SDK_ROOT}/Demo/wm_master_spi_demo.c
${SDK_ROOT}/Demo/wm_rtc_demo.c
${SDK_ROOT}/Demo/wm_timer_demo.c
${SDK_ROOT}/Demo/wm_pmu_demo.c
${SDK_ROOT}/Demo/wm_crypt_hard_demo.c
${SDK_ROOT}/Demo/wm_rsa_demo.c
${SDK_ROOT}/Demo/wm_connect_net_demo.c
${SDK_ROOT}/Demo/wm_http_demo.c
${SDK_ROOT}/Demo/wm_wps_demo.c
${SDK_ROOT}/Demo/wm_websockets_demo.c
${SDK_ROOT}/Demo/wm_ssl_server_demo.c
${SDK_ROOT}/Demo/wm_ntp_demo.c
${SDK_ROOT}/Demo/wm_mqtt_demo.c
${SDK_ROOT}/Demo/wm_https_demo.c
${SDK_ROOT}/Demo/wm_scan_demo.c
${SDK_ROOT}/Demo/wm_log_demo.c
${SDK_ROOT}/Demo/wm_sck_client_demo.c
${SDK_ROOT}/Demo/wm_sck_server_demo.c



#Common
${SDK_ROOT}/Platform/Common/fwup/wm_fwup.c
${SDK_ROOT}/Platform/Common/mem/wm_mem.c
${SDK_ROOT}/Platform/Common/Params/wm_param.c
${SDK_ROOT}/Platform/Common/task/wm_wl_mbox.c
${SDK_ROOT}/Platform/Common/task/wm_wl_task.c
${SDK_ROOT}/Platform/Common/task/wm_wl_timers.c
${SDK_ROOT}/Platform/Common/utils/utils.c
${SDK_ROOT}/Platform/Common/crypto/digest/hmac.c
${SDK_ROOT}/Platform/Common/crypto/digest/md2.c
${SDK_ROOT}/Platform/Common/crypto/digest/md4.c
${SDK_ROOT}/Platform/Common/crypto/digest/sha224.c
${SDK_ROOT}/Platform/Common/crypto/digest/sha384.c
${SDK_ROOT}/Platform/Common/crypto/digest/sha512.c
${SDK_ROOT}/Platform/Common/crypto/keyformat/asn1.c
${SDK_ROOT}/Platform/Common/crypto/keyformat/base64.c
${SDK_ROOT}/Platform/Common/crypto/keyformat/x509.c
${SDK_ROOT}/Platform/Common/crypto/math/pstm_mul_comba.c
${SDK_ROOT}/Platform/Common/crypto/prng/prng.c
${SDK_ROOT}/Platform/Common/crypto/prng/yarrow.c
${SDK_ROOT}/Platform/Common/crypto/pubkey/dh.c
${SDK_ROOT}/Platform/Common/crypto/pubkey/ecc.c
${SDK_ROOT}/Platform/Common/crypto/pubkey/pkcs.c
${SDK_ROOT}/Platform/Common/crypto/pubkey/pubkey.c
${SDK_ROOT}/Platform/Common/crypto/pubkey/rsa.c
${SDK_ROOT}/Platform/Common/crypto/symmetric/aesGCM.c
${SDK_ROOT}/Platform/Common/crypto/symmetric/des3.c
${SDK_ROOT}/Platform/Common/crypto/symmetric/idea.c
${SDK_ROOT}/Platform/Common/crypto/symmetric/rc2.c
${SDK_ROOT}/Platform/Common/crypto/symmetric/seed.c
${SDK_ROOT}/Platform/Common/crypto/wm_crypto_hard.c

#Drivers
${SDK_ROOT}/Platform/Drivers/adc/wm_adc.c
${SDK_ROOT}/Platform/Drivers/cpu/wm_cpu.c
${SDK_ROOT}/Platform/Drivers/dma/wm_dma.c
${SDK_ROOT}/Platform/Drivers/efuse/wm_efuse.c
${SDK_ROOT}/Platform/Drivers/flash/wm_fls.c
${SDK_ROOT}/Platform/Drivers/flash/wm_fls_gd25qxx.c
${SDK_ROOT}/Platform/Drivers/gpio/wm_gpio.c
${SDK_ROOT}/Platform/Drivers/gpio/wm_gpio_afsel.c
${SDK_ROOT}/Platform/Drivers/hspi/wm_hspi.c
${SDK_ROOT}/Platform/Drivers/i2c/wm_i2c.c
${SDK_ROOT}/Platform/Drivers/irq/wm_irq.c
${SDK_ROOT}/Platform/Drivers/pwm/wm_pwm.c
${SDK_ROOT}/Platform/Drivers/pmu/wm_pmu.c
${SDK_ROOT}/Platform/Drivers/rtc/wm_rtc.c
${SDK_ROOT}/Platform/Drivers/spi/wm_hostspi.c
${SDK_ROOT}/Platform/Drivers/timer/wm_timer.c
${SDK_ROOT}/Platform/Drivers/uart/wm_uart.c
${SDK_ROOT}/Platform/Drivers/watchdog/wm_watchdog.c
${SDK_ROOT}/Platform/Drivers/internalflash/wm_internal_fls.c
${SDK_ROOT}/Platform/Drivers/i2s/wm_i2s.c
${SDK_ROOT}/Platform/Drivers/io/wm_io.c
${SDK_ROOT}/Platform/Drivers/lcd/wm_lcd.c
${SDK_ROOT}/Platform/Drivers/7816/wm_7816.c

#SYS
${SDK_ROOT}/Platform/Sys/wm_main.c
${SDK_ROOT}/Platform/Sys/tls_sys.c

#LWIP
${SDK_ROOT}/Src/Network/api2.0.3/tls_sockets.c
${SDK_ROOT}/Src/Network/api2.0.3/tls_netconn.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/dns.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/def.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/init.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/mem.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/memp.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/netif.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/pbuf.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/raw.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/stats.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/sys.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/tcp.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/tcp_in.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/tcp_out.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/udp.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/inet_chksum.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ip.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/timeouts.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/alg.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv4/ip4_frag.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv4/ip4_addr.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv4/ip4.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv4/dhcp.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv4/etharp.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv4/igmp.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv4/icmp.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv4/autoip.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/ip6_frag.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/ip6_addr.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/ip6.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/dhcp6.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/ethip6.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/icmp6.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/inet6.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/mld6.c
${SDK_ROOT}/Src/Network/lwip2.0.3/core/ipv6/nd6.c
${SDK_ROOT}/Src/Network/lwip2.0.3/sys_arch.c
${SDK_ROOT}/Src/Network/lwip2.0.3/netif/ethernetif.c
${SDK_ROOT}/Src/Network/lwip2.0.3/netif/ethernet.c
${SDK_ROOT}/Src/Network/lwip2.0.3/netif/wm_ethernet.c
${SDK_ROOT}/Src/Network/lwip2.0.3/api/tcpip.c
${SDK_ROOT}/Src/Network/lwip2.0.3/api/api_lib.c
${SDK_ROOT}/Src/Network/lwip2.0.3/api/api_msg.c
${SDK_ROOT}/Src/Network/lwip2.0.3/api/err.c
${SDK_ROOT}/Src/Network/lwip2.0.3/api/netbuf.c
${SDK_ROOT}/Src/Network/lwip2.0.3/api/netdb.c
${SDK_ROOT}/Src/Network/lwip2.0.3/api/netifapi.c
${SDK_ROOT}/Src/Network/lwip2.0.3/api/sockets.c

#FreeRTOS
${SDK_ROOT}/Src/OS/RTOS/source/croutine.c
${SDK_ROOT}/Src/OS/RTOS/source/heap_2.c
${SDK_ROOT}/Src/OS/RTOS/source/heap_3.c
${SDK_ROOT}/Src/OS/RTOS/source/list.c
${SDK_ROOT}/Src/OS/RTOS/source/queue.c
${SDK_ROOT}/Src/OS/RTOS/source/rtostimers.c
${SDK_ROOT}/Src/OS/RTOS/source/tasks.c
${SDK_ROOT}/Src/OS/RTOS/wm_osal_rtos.c
${SDK_ROOT}/Src/OS/RTOS/ports/port_m3_gcc.c

#APP

##cJSON
${SDK_ROOT}/Src/App/cJSON/cJSON.c

##dhcpserver
${SDK_ROOT}/Src/App/dhcpserver/dhcp_server.c

##dnsserver
${SDK_ROOT}/Src/App/dnsserver/dns_server.c

##easylogger
${SDK_ROOT}/Src/App/easylogger/src/elog.c
${SDK_ROOT}/Src/App/easylogger/src/elog_async.c
${SDK_ROOT}/Src/App/easylogger/src/elog_buf.c
${SDK_ROOT}/Src/App/easylogger/src/elog_utils.c
${SDK_ROOT}/Src/App/easylogger/port/elog_port.c

##httpclient
${SDK_ROOT}/Src/App/httpclient/wm_http_compile.c

##iperf
${SDK_ROOT}/Src/App/iperf/iperf_api.c
${SDK_ROOT}/Src/App/iperf/iperf_client_api.c
${SDK_ROOT}/Src/App/iperf/iperf_error.c
${SDK_ROOT}/Src/App/iperf/iperf_main.c
${SDK_ROOT}/Src/App/iperf/iperf_net.c
${SDK_ROOT}/Src/App/iperf/iperf_server_api.c
${SDK_ROOT}/Src/App/iperf/iperf_tcp.c
${SDK_ROOT}/Src/App/iperf/iperf_udp.c
${SDK_ROOT}/Src/App/iperf/iperf_util.c
${SDK_ROOT}/Src/App/iperf/iperf_locale.c
${SDK_ROOT}/Src/App/iperf/tcp_info.c
${SDK_ROOT}/Src/App/iperf/tcp_window_size.c
${SDK_ROOT}/Src/App/iperf/iperf_timer.c
${SDK_ROOT}/Src/App/iperf/iperf_units.c
${SDK_ROOT}/Src/App/iperf/wm_perf.c

##libcoap
${SDK_ROOT}/Src/App/libcoap/address.c
${SDK_ROOT}/Src/App/libcoap/async.c
${SDK_ROOT}/Src/App/libcoap/block.c
${SDK_ROOT}/Src/App/libcoap/coap_time.c
${SDK_ROOT}/Src/App/libcoap/debug.c
${SDK_ROOT}/Src/App/libcoap/encode.c
${SDK_ROOT}/Src/App/libcoap/hashkey.c
${SDK_ROOT}/Src/App/libcoap/option.c
${SDK_ROOT}/Src/App/libcoap/pdu.c
${SDK_ROOT}/Src/App/libcoap/resource.c
${SDK_ROOT}/Src/App/libcoap/str.c
${SDK_ROOT}/Src/App/libcoap/subscribe.c
${SDK_ROOT}/Src/App/libcoap/mem_libcoap.c
${SDK_ROOT}/Src/App/libcoap/coap_io_lwip.c
${SDK_ROOT}/Src/App/libcoap/net.c

##libwebsockets-2.1-stable
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/base64-decode.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/client.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/client-handshake.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/client-parser.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/context.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/handshake.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/header.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/libwebsockets.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/lws-plat-wm.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/output.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/parsers.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/pollfd.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/service.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/ssl.c
${SDK_ROOT}/Src/App/libwebsockets-2.1-stable/ssl-client.c

##lwm2m-wakaama
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/block1.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/bootstrap.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/data.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/discover.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/json.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/json_common.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/liblwm2m.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/list.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/management.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/objects.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/observe.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/packet.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/registration.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/senml_json.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/tlv.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/transaction.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/uri.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/utils.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/lightclient/lightclient.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/shared/commandline.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/shared/connection.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/shared/memtrace.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/shared/platform.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/lightclient/object_device.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/lightclient/object_security.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/lightclient/object_server.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/examples/lightclient/test_object.c
${SDK_ROOT}/Src/App/lwm2m-wakaama/core/er-coap-13/er-coap-13.c

##matrixssl
${SDK_ROOT}/Src/App/matrixssl/cipherSuite.c
${SDK_ROOT}/Src/App/matrixssl/hsHash.c
${SDK_ROOT}/Src/App/matrixssl/matrixssl.c
${SDK_ROOT}/Src/App/matrixssl/matrixsslApi.c
${SDK_ROOT}/Src/App/matrixssl/prf.c
${SDK_ROOT}/Src/App/matrixssl/psk.c
${SDK_ROOT}/Src/App/matrixssl/sslDecode.c
${SDK_ROOT}/Src/App/matrixssl/sslEncode.c
${SDK_ROOT}/Src/App/matrixssl/sslv3.c
${SDK_ROOT}/Src/App/matrixssl/tls.c
${SDK_ROOT}/Src/App/matrixssl/core/corelib.c
${SDK_ROOT}/Src/App/matrixssl/core/osdep.c

##mDNS
${SDK_ROOT}/Src/App/mDNS/mDNSCore/mDNS.c
${SDK_ROOT}/Src/App/mDNS/mDNSPosix/mDNSPosix.c

##mqtt
${SDK_ROOT}/Src/App/mqtt/libemqtt.c

##ntp
${SDK_ROOT}/Src/App/ntp/ntp_client.c

##oneshotconfig
${SDK_ROOT}/Src/App/oneshotconfig/wm_wifi_oneshot.c
${SDK_ROOT}/Src/App/oneshotconfig/wm_oneshot_airkiss.c
${SDK_ROOT}/Src/App/oneshotconfig/wm_oneshot_lsd.c


##OTA
${SDK_ROOT}/Src/App/OTA/wm_http_fwup.c
${SDK_ROOT}/Src/App/OTA/wm_socket_fwup.c

##ping
${SDK_ROOT}/Src/App/ping/ping.c

##polarssl
${SDK_ROOT}/Src/App/polarssl/library/asn1parse.c
${SDK_ROOT}/Src/App/polarssl/library/base64.c
${SDK_ROOT}/Src/App/polarssl/library/cipher.c
${SDK_ROOT}/Src/App/polarssl/library/cipher_wrap.c
${SDK_ROOT}/Src/App/polarssl/library/error.c
${SDK_ROOT}/Src/App/polarssl/library/md.c
${SDK_ROOT}/Src/App/polarssl/library/md_wrap.c
${SDK_ROOT}/Src/App/polarssl/library/pem.c
${SDK_ROOT}/Src/App/polarssl/library/rsa.c
${SDK_ROOT}/Src/App/polarssl/library/ssl_cli.c
${SDK_ROOT}/Src/App/polarssl/library/ssl_tls.c
${SDK_ROOT}/Src/App/polarssl/library/x509parse.c
${SDK_ROOT}/Src/App/polarssl/library/polarssl_bignum.c
${SDK_ROOT}/Src/App/polarssl/library/polarssl_debug.c
${SDK_ROOT}/Src/App/polarssl/library/polarssl_md5.c
${SDK_ROOT}/Src/App/polarssl/library/polarssl_sha1.c
${SDK_ROOT}/Src/App/polarssl/library/arc4.c

##sslserver
${SDK_ROOT}/Src/App/sslserver/wm_ssl_server.c

##web
${SDK_ROOT}/Src/App/web/fs.c
${SDK_ROOT}/Src/App/web/httpd.c
${SDK_ROOT}/Src/App/web/web.c

##wm_atcmd
${SDK_ROOT}/Src/App/wm_atcmd/wm_cmd.c



)

#添加SimpleMQTTGateWayStack库
add_subdirectory(lib/SimpleMQTTGateWayStack/lib)

#添加MQTT移植
file(GLOB  PAHO_PORT_C_FILES lib/MQTT/*.c)
list(APPEND PAHO_SRCS
${PAHO_MQTTPACKET_C_FILES}
${PAHO_PORT_C_FILES}
)
add_library(PAHO_MQTT STATIC ${PAHO_SRCS})
target_include_directories(PAHO_MQTT
PUBLIC lib/MQTT/
)
target_compile_definitions(PAHO_MQTT
PUBLIC MQTTCLIENT_PLATFORM_HEADER=MQTTFreeRTOS_LWIP.h
)
target_link_libraries(PAHO_MQTT SMGS)

#使用源代码编译的库文件
add_library(SDK_SOURCE_LIB STATIC ${SDK_SRCS})

#预先编译的库文件
list(APPEND SDK_PRECOMPILED_LIBS
#OnrShot
${SDK_ROOT}/Src/App/oneshotconfig/lib_gcc/libairkiss_log.a

#WLAN
${SDK_ROOT}/Lib/GNU/wlan.a
)

if(NOT DEFINED MAIN_SRCS)
	set(MAIN_SRCS ${SDK_ROOT}/App/main.c )
endif()

list(APPEND MAIN_SRCS

#Boot
${SDK_ROOT}/Platform/Boot/gcc/startup_ARMCM3.S
${SDK_ROOT}/Platform/Boot/gcc/misc.c
${SDK_ROOT}/Platform/Boot/gcc/retarget_gcc.c

)

if(NOT DEFINED MAIN_INCLUDE_DIRS)
	set(MAIN_INCLUDE_DIRS ./)
endif()

list(APPEND  MAIN_INCLUDE_DIRS  ${SDK_INCLUDE_DIRS})

#添加定义
add_definitions(" -DWM_W600=1 -D_IN_ADDR_T_DECLARED -D__MACHINE_ENDIAN_H__ -D_TIMEVAL_DEFINED -D__INSIDE_CYGWIN_NET__")

#Kconfig(使用Kconfig进行配置)
option(USE_KCONFIG "use kconfig" ON)

if(${USE_KCONFIG})

    add_definitions(" -DUSE_KCONFIG=1 ")

    find_program(PYTHON
               NAMES python3 python python2
               REQUIRED
               )
    message("python path: ${PYTHON}")
    #安装依赖
    execute_process(COMMAND ${PYTHON} -m pip install -r  ${CMAKE_CURRENT_SOURCE_DIR}/requirement.txt
                      RESULT_VARIABLE PYTHON_INSTALL_RESULT)
    if(PYTHON_INSTALL_RESULT EQUAL 0)
    message("install from requirement.txt success")
    else()
    message(FATAL_ERROR "install from requirement.txt error")
    endif()

    #生成config.h
    add_custom_command(OUTPUT config.h
                    COMMAND ${PYTHON} -m genconfig --header-path config.h
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    )


    if(CMAKE_HOST_WIN32)
        #menuconfig 目标(windows)
        add_custom_target(menuconfig cmd.exe /C start cmd.exe /c ${PYTHON} -m menuconfig
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  USES_TERMINAL
                  )
    else()
        #menuconfig 目标(非windows)
        add_custom_target(menuconfig  ${PYTHON} -m menuconfig
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  USES_TERMINAL
                  )
    endif()

    #将config.h添加至MAIN_SRCS
    list(APPEND MAIN_SRCS
         config.h )


endif()

#设置头文件
include_directories(${MAIN_INCLUDE_DIRS})

#添加可执行文件
add_executable(${PROJECT_NAME} ${MAIN_SRCS})
target_link_libraries(${PROJECT_NAME} SDK_SOURCE_LIB PAHO_MQTT ${SDK_PRECOMPILED_LIBS} )

#生成bin文件
add_custom_target(${PROJECT_NAME}.bin ALL
				 COMMAND ${CMAKE_OBJCOPY} --output-target=binary -S -g -x -X ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
				 DEPENDS ${PROJECT_NAME}
				 )

#准备wm_tool
find_program(WM_TOOL
               NAMES wm_tool
               PATHS ${SDK_ROOT}/Tools ${CMAKE_BINARY_DIR}/
               NO_CACHE
               )
if(NOT EXISTS ${WM_TOOL})
    message("wm_tool is not found,try to compile!")
    #使用C编译器编译
    find_program(CC NAMES cc gcc REQUIRED)
    message("cc path: ${CC}")
    execute_process(COMMAND ${CC} -pthread ${SDK_ROOT}/Tools/src/wm_tool.c  -o ${CMAKE_BINARY_DIR}/wm_tool)
    find_program(WM_TOOL
               NAMES wm_tool
               PATHS  ${CMAKE_BINARY_DIR}/ ${SDK_ROOT}/Tools
               NO_CACHE
               REQUIRED
               )
    message("wm_tool path: ${WM_TOOL}" )
else()
    message("wm_tool path: ${WM_TOOL}" )
endif()

if(${BUILD_FLASH_2M})
    set(GREATE_IMG_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin -sb ${SDK_ROOT}/Bin/secboot.img  -fc compress -it 2M -ua 100000 -ra 10100 -df -o ${PROJECT_NAME})
else()
    set(GREATE_IMG_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin -sb ${SDK_ROOT}/Bin/secboot.img  -fc compress -it 1M -ua 90000 -ra 10100 -df -o ${PROJECT_NAME})
endif()

#生成其它镜像文件（包括fls文件）
add_custom_target(${PROJECT_NAME}.fls ALL
				 COMMAND ${WM_TOOL} ${GREATE_IMG_FLAGS}
				 DEPENDS ${PROJECT_NAME}.bin
				 )

#flash 目标 （使用 make flash WM_PORT=串口 烧录）

##默认的烧录串口
##环境变量
if(NOT DEFINED ENV{WM_PORT})
    set(ENV{WM_PORT} ttyUSB0)
endif()


add_custom_target(flash
                    COMMAND ${WM_TOOL} -c $ENV{WM_PORT} -eo all -dl ${PROJECT_NAME}.fls
                    DEPENDS ${PROJECT_NAME}.fls
                    )



#run目标
add_custom_target(run
                   COMMAND ${WM_TOOL} -c $ENV{WM_PORT} -eo all -dl ${PROJECT_NAME}.fls -sl str -ws 115200
                   DEPENDS ${PROJECT_NAME}.fls
                  )

