package EchoServer;

import java.nio.charset.Charset;

import io.netty.buffer.ByteBuf;
import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;

/**
 * Created by imb on 2017. 5. 26..
 */
public class EchoClientHandler extends ChannelInboundHandlerAdapter {
	@Override
	public void channelActive(ChannelHandlerContext context) {
		String sendMessage = "Hello, Netty!";

		ByteBuf messageBuffer = Unpooled.buffer();
		messageBuffer.writeBytes(sendMessage.getBytes());

		StringBuilder builder = new StringBuilder();
		builder.append("전송한 문자열[");
		builder.append(sendMessage);
		builder.append("]");

		System.out.println(builder.toString());

		context.writeAndFlush(messageBuffer);
	}

	@Override
	public void channelRead(ChannelHandlerContext context, Object msg) {
		String readMessage = ((ByteBuf) msg).toString(Charset.defaultCharset());

		StringBuilder builder = new StringBuilder();
		builder.append("수신한 문자열[");
		builder.append(readMessage);
		builder.append("]");

		System.out.println(builder.toString());
	}

	@Override
	public void channelReadComplete(ChannelHandlerContext context) {
		context.close();
	}

	@Override
	public void exceptionCaught(ChannelHandlerContext context, Throwable cause) {
		cause.printStackTrace();
		context.close();
	}
}
