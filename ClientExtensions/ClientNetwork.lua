function WriteMessage(size)
	local writer = { id = _WriteMessage(size) }

	function writer:WriteUInt8(value)
	 _WriteUInt8(self.id,value)
		return self
	end

	function writer:Send()
		_SendMessage(self.id)
		return self
	end

	return writer
end

function __ReadMessage()
	local reader = {}
	function reader:ReadUInt8()
		return _ReadUInt8()
	end
	return reader
end

-- todo: not sure if we can do real callbacks,
-- so we will just cheat a little and
-- execute the string '__FireMessage()' whenever
-- we receive a message in c++

__callbacks = {}
function OnMessage(cb)
	table.insert(__callbacks,cb)
end

function __FireMessage()
	for k,v in pairs(__callbacks) do
		v(__ReadMessage(v))
	end
end