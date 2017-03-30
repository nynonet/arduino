package net.nynonet;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;

public class MainActivity extends AppCompatActivity {

    TextView  lab_red, lab_gre, lab_blu, lab_status, lbCor;
    SeekBar sRed, sGre, sBlu;
    Button botao;
    NynoBlue nynoBlue;
    private SharedPreferences myConfig;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        AdView mAdView = (AdView) findViewById(R.id.adView);

        AdRequest adRequest = new AdRequest.Builder().build();
        mAdView.loadAd(adRequest);

        Preferencias();

        lab_red = (TextView) findViewById(R.id.lRed);
        lab_gre = (TextView) findViewById(R.id.lGre);
        lab_blu = (TextView) findViewById(R.id.lBlu);
        lab_status = (TextView) findViewById(R.id.lStatus);
        botao = (Button) findViewById(R.id.btnAtivar);
        lbCor = (TextView) findViewById(R.id.CorFundo);

        sRed = (SeekBar) findViewById(R.id.pRed);
        sGre = (SeekBar) findViewById(R.id.pGre);
        sBlu = (SeekBar) findViewById(R.id.pBlu);

        sRed.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                SendComando( myConfig.getString("cfgRed", "R")+ (255-progress) );
                lab_red.setText(getString(R.string.lbRed) + "   "+ (progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        sGre.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                SendComando( myConfig.getString("cfgGre", "G")+ (255-progress) );
                lab_gre.setText(getString(R.string.lbGre) + "   "+ (progress));

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        sBlu.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                SendComando( myConfig.getString("cfgBlu", "B")+ (255-progress) );
                lab_blu.setText(getString(R.string.lbBlu) + "   "+ (progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        nynoBlue = new NynoBlue(this, lab_status);
        nynoBlue.isAtivarBlue();
        nynoBlue.SetAparelho( myConfig.getString("cfgBlue", "") );

        botao.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!nynoBlue.IsConectado()) {
                    if (nynoBlue.Conectar()) {
                        botao.setText(getString(R.string.lbDesConectar));
                    }
                } else {
                    nynoBlue.Desconectar();
                    botao.setText(getString(R.string.lbConectar));
                }
            }
        });

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        super.onCreateOptionsMenu(menu);
        MenuInflater m = getMenuInflater();
        m.inflate(R.menu.menu_opcoes, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == R.id.mParametros) {
            Intent im = new Intent(this, preferencia.class);
            startActivity(im);
            return true;
        }

        if (item.getItemId() == R.id.mSobre) {
            Intent intent = new Intent(this, Sobre.class);
            startActivity(intent);
            return true;
        }

        return false;
    }

    private void SendComando(String c) {

        if (nynoBlue.IsConectado()) {
            nynoBlue.EnviarDados(c);
        }

        int vermelho = sRed.getProgress();
        int verde = sGre.getProgress();
        int azul = sBlu.getProgress();
        if ((verde+vermelho+azul) > 0) {
            lbCor.setBackgroundColor(Color.rgb(vermelho,verde,azul));
        } else {
            lbCor.setBackgroundColor(Color.TRANSPARENT);
        }
    }

    private void Preferencias() {
        myConfig = PreferenceManager.getDefaultSharedPreferences(this);
    }

}
