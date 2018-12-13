package com.example.tharunparackal.lasertag;

import android.app.Activity;
//import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.content.Intent;
import android.widget.Button;


public class MainActivity extends Activity
{
    public Button buttonSetup;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void buttonOnClick (View v) // do something when a button is clicked
    {
        switch(v.getId()) // finds what button was pressed
        {
            case R.id.buttonSetup:
                startActivity(new Intent(getApplicationContext(), SetupActivity.class)); // starts setup activity

        }
    }
}
