package EchoServer;

import java.nio.charset.Charset;

import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;

/**
 * Created by imb on 2017. 5. 26..
 */
public class EchoServerHandler extends ChannelInboundHandlerAdapter {
	@Override
	public void channelRead(ChannelHandlerContext context, Object msg) {
		String readMessage = ((ByteBuf) msg).toString(Charset.defaultCharset());

		System.out.println("수신한 문자열 [" + readMessage.trim() + "]");

		context.write(msg);
	}

	@Override
	public void channelReadComplete(ChannelHandlerContext context) {
		context.flush();
	}
}
