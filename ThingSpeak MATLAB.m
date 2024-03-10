% Channel IDs and APIs
readChannelID = ...;
readAPIKey = 'Enter API key of associated Server channel'; 

writeChannelID1 = ...;
writeAPIKey1 = 'Enter API key of Client1 channel';

writeChannelID2 = ...;
writeAPIKey2 = 'Enter API key of Client2 channel';


% Field IDs
FieldID = 1;

F_dec = 0;
F_dec = thingSpeakRead(readChannelID,'Fields',FieldID,'ReadKey',readAPIKey);

F_dec(isnan(F_dec)) = 0;

% Calculate object locations 
NumObjects = 2;
RoomNo = "Room 1";

F_bin = fliplr(my_int2bit(F_dec, NumObjects));

if F_bin(1, 1) == 1
    thingSpeakWrite(writeChannelID1, 'Fields', FieldID, 'Values', RoomNo, 'WriteKey', writeAPIKey1);
end
if F_bin(1, 2) == 1
    thingSpeakWrite(writeChannelID2, 'Fields', FieldID, 'Values', RoomNo, 'WriteKey', writeAPIKey2);
end

function b = my_int2bit(dec, n)
    x = [];
    y = 2;
    in = dec;

    if dec >= (2^16 -1)
        fprintf('This number is too big')
    else
        ii = 1;
        while n > 0
            r = logical(rem(in,y^ii));
            x = [r x];
            in = in - r*2^(ii-1);
            ii = ii+1;
            n = n - 1;
        end
    end

    b = x;
end  