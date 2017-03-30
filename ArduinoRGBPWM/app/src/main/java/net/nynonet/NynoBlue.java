package net.nynonet;


import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.support.v4.app.ActivityCompat;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.List;
import java.util.Set;
import java.util.UUID;

/**
 * Created by Andeson on 09/07/16.
 */
public class NynoBlue {
    private BluetoothAdapter blueAdapter;
    private BluetoothDevice bluetoothDevice;
    private Set<BluetoothDevice> pareados;
    private BluetoothServerSocket bluetoothServerSocket;
    private BluetoothSocket bluetoothSocket;
    private TextView LbBlueTooth;

    public UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");


    private int pcEnviados = 0;
    private int pcRecebidos = 0;
    private String MsgRetorno;
    private Boolean IsConecado = false;

    private Activity ControlePai;

    /**
     * Classe desenvolvida para controlar dispositivos bluetooth
     *
     * @param pai      deve-se informar qual a activity pai que será usada para interação
     * @param textView deve-se informa qual o TextView vai receber o status do bluetooth
     */
    public NynoBlue(Activity pai, TextView textView) {
        this.ControlePai = pai;
        this.LbBlueTooth = textView;

        LbBlueTooth.setText(R.string.lbBlueNotCfg);
        IsConecado = false;
//        Log.i("Nyno", "aaaa");
    }

    /**
     * Retorna a lista de dispositivos bluetooth pareados
     *
     * @return lista de dispositivos pareados.
     */
    public List<BluetoothDevice> AtualizaListaBluetooth() {

        if (!isAtivarBlue()) {
            MsgTela("Bluetooth inoperante!");
            return null;
        }

        List<BluetoothDevice> lista = null;
        try {
            pareados = blueAdapter.getBondedDevices();
            if (pareados.size() > 0) {
                for (BluetoothDevice device : pareados) {
                    lista.add(device);
                }
            }
        } catch (Exception e) {
        }

        return lista;
    }

    public boolean Conectar() {

        if (bluetoothDevice != null) {
            try {
                bluetoothSocket = bluetoothDevice.createInsecureRfcommSocketToServiceRecord(uuid);
                Log.e("Nyno", "conectando em " + bluetoothDevice.getName());
                bluetoothSocket.connect();
                LbBlueTooth.setText("Conectado em " + bluetoothDevice.getName());
                //RecebeDados();
                IsConecado = true;

                return true;
            } catch (Exception e) {
                LbBlueTooth.setText("Falha no conectar em " + bluetoothDevice.getName());
                Log.e("Nyno", e.getMessage());
                IsConecado = false;
                return false;
            }
        } else {
            //problema no device
            LbBlueTooth.setText("Dispositivo não configurado!");
            Log.e("Nyno", "Não conectado!");
            IsConecado = false;
            return false;
        }

    }

    public boolean IsConectado(){
        return IsConecado;
    }

    public void Desconectar() {
        try {
            bluetoothSocket.close();
            LbBlueTooth.setText("Desconectado!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Retorna a mensagem recebida pelo arduino.
     * @return mensagem
     */
    public String MsgRetorno() {
        return  MsgRetorno;
    }

    /**
     * Função para enviar os comando para o bluetooth
     * @param pacote - Parâmetro para enviar o comando/instrução
     */
    public void EnviarDados(String pacote) {
        try {
            OutputStream envia = bluetoothSocket.getOutputStream();
            envia.write( pacote.getBytes() );
            pcEnviados += pacote.getBytes().length;
        } catch (Exception e) {
            LbBlueTooth.setText("Falha no enviar e receber dados!");
        }

        RecebeDados();
    }

    private void RecebeDados(){
        try {
            InputStream recebe = bluetoothSocket.getInputStream();
            try {
                if (recebe.available()>0) {
                    byte[] buffer;
                    buffer = new byte[1024];
                    int b = recebe.read(buffer);
                    MsgRetorno = new String(buffer, 0, b);
                }
            } catch (Exception e) {

            }


            pcRecebidos += MsgRetorno.getBytes().length;
        } catch (Exception e) {

        }

    }

    /**
     * Função para verificar se o bluetooth encontra-se ativo.<p>
     * se estiver ativo retorna TRUE "sim" se não tenta ativa-ló
     * caso seja ativo retorna TRUE se não envia msg informando erro e retorna FALSE "não"
     */
    public boolean isAtivarBlue() {
        blueAdapter = BluetoothAdapter.getDefaultAdapter();

        if (blueAdapter.isEnabled() == true) {
            return true;
        } else {
            try {
                Intent intent = new Intent(blueAdapter.ACTION_REQUEST_ENABLE);
                ActivityCompat.startActivityForResult(ControlePai, intent, 1, null);
                return true;
            } catch (Exception e) {
                MsgTela("Erro no Ativar bluetooth!");
                return false;
            }
        }
    }

    /**
     * Função para identificar com qual dispositivo bluetooth irá trabalhar. <p>
     *
     * @param BtMac deve ser informado o código Adderess do dispositivo.
     */
    public void SetAparelho(String BtMac) {
        try {
            pareados = blueAdapter.getBondedDevices();
            bluetoothDevice = null;

            LbBlueTooth.setText(R.string.lbBlueNotCfg); // msg não conectado!

            if (pareados.size() > 0) {
                for (BluetoothDevice device : pareados) {
                    if (device.getAddress().equals(BtMac)) {
                        bluetoothDevice = device;
                        LbBlueTooth.setText(R.string.lbBlueCon + " " + device.getName()); //mostra em quem está conectado.
                    }
                }
            }

        } catch (Exception e) {

        }
    }

    /**
     * Função que retorna a quantidade de pacotes Enviados ao dispositivo Bluetooth
     *
     * @return retorna o valor em Bytes
     */
    public int getPcEnviados() {
        return this.pcEnviados;
    }

    /**
     * Função que retorna a quantidade de pacotes Recebidos ao dispositivo Bluetooth
     *
     * @return retorna o valor em Bytes
     */
    public int getPcRecebidos() {
        return this.pcRecebidos;
    }

    private void MsgTela(String Msg) {
        Toast toast = Toast.makeText(ControlePai, Msg, Toast.LENGTH_LONG);
        toast.show();
        Log.i("Nyno", Msg);
    }

}
