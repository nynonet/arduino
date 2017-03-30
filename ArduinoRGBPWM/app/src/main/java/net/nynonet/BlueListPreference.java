package net.nynonet;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.preference.ListPreference;
import android.util.AttributeSet;

import java.util.Set;

/**
 * Created by Andeson on 14/04/2016.
 */
public class BlueListPreference extends ListPreference {

    public BlueListPreference(Context context, AttributeSet atrs){
        super( context, atrs );
        BluetoothAdapter bta = BluetoothAdapter.getDefaultAdapter();
        Set<BluetoothDevice> pairedDevices = bta.getBondedDevices();
        CharSequence[] entries = new CharSequence[1];
        CharSequence[] entryValues = new CharSequence[1];
        entries[0] = "No Devices";
        entryValues[0] = "";
        if ( pairedDevices != null ) {
            entries = new CharSequence[pairedDevices.size()];
            entryValues = new CharSequence[pairedDevices.size()];
            int i = 0;
            for (BluetoothDevice dev : pairedDevices) {
                entries[i] = dev.getName();
                entryValues[i] = dev.getAddress();
                i++;
            }
        }
        setEntries(entries);
        setEntryValues(entryValues);
    }

    public BlueListPreference(Context context) {
        this(context, null);
    }

}
