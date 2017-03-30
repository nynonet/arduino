package net.nynonet;

import android.os.Bundle;
import android.preference.PreferenceActivity;

/**
 * Created by Andeson on 25/06/16.
 */
public class preferencia extends PreferenceActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTheme( R.style.AppTheme );
        super.onCreate(savedInstanceState);

        addPreferencesFromResource(R.xml.preferencias);
    }
}
