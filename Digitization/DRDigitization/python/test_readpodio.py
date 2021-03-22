from EventStore import EventStore
import ROOT


filename = "pippo.root"
hitfilename = "/its/home/iv41/scratch/G4/SingleParticle/pions_Escan_tower1_G4_10.7/run_0001/podio/run_0001_pi-_ene_5_tower_1_openAngle_0_2_podio.root"
ofilename = "output.root"

store = EventStore(filename)
storehit = EventStore(hitfilename)

ofile = ROOT.TFile(ofilename,"recreate")
ofile.mkdir("Digitization")

ofile.cd("Digitization")

h_c_fiber_energy = ROOT.TH1F("h_c_fiber_energy","",100,0,-1)
h_s_fiber_energy = ROOT.TH1F("h_s_fiber_energy","",100,0,-1)
h_c_fiber_time = ROOT.TH1F("h_c_fiber_time","",100,0,-1)
h_s_fiber_time = ROOT.TH1F("h_s_fiber_time","",100,0,-1)

h_c_energy = ROOT.TH1F("h_c_energy","",100,0,-1)
h_s_energy = ROOT.TH1F("h_s_energy","",100,0,-1)
h_c_time = ROOT.TH1F("h_c_time","",100,0,-1)
h_s_time = ROOT.TH1F("h_s_time","",100,0,-1)

h_n_s_fiber = ROOT.TH1F("h_n_s_fiber","",100,0,-1)
h_n_c_fiber = ROOT.TH1F("h_n_c_fiber","",100,0,-1)

h_c_ratio_simdigi = ROOT.TH1F("h_c_ratio_simdigi","",100,0,-1)
h_s_ratio_simdigi = ROOT.TH1F("h_s_ratio_simdigi","",100,0,-1)

for i, event in enumerate(store):
    if i % 1000 == 0:
        print('reading event', i)
    c_hits = event.get("C_CalorimeterHits")
    s_hits = event.get("S_CalorimeterHits")
    tot_s_energy = 0
    tot_c_energy = 0
    tot_s_time = 0
    tot_c_time = 0
    n_s_fiber = 0
    n_c_fiber = 0
    for hit in c_hits:
        h_c_fiber_energy.Fill(hit.getEnergy())
        h_c_fiber_time.Fill(hit.getTime())
        tot_c_energy = tot_c_energy + hit.getEnergy()
        tot_c_time = tot_c_time + hit.getTime()
        n_c_fiber = n_c_fiber + 1
    for hit in s_hits:
        h_s_fiber_energy.Fill(hit.getEnergy())
        h_s_fiber_time.Fill(hit.getTime())
        tot_s_energy = tot_s_energy + hit.getEnergy()
        tot_s_time = tot_s_time + hit.getTime()
        n_s_fiber = n_s_fiber + 1
        
    if (n_s_fiber != 0):
        tot_s_time = tot_s_time/n_s_fiber
    if (n_c_fiber != 0):
        tot_c_time = tot_c_time/n_c_fiber

    h_c_energy.Fill(tot_c_energy)
    h_s_energy.Fill(tot_s_energy)
    h_c_time.Fill(tot_c_time)
    h_s_time.Fill(tot_s_time)

    h_n_s_fiber.Fill(n_s_fiber + 0.5)
    h_n_c_fiber.Fill(n_c_fiber + 0.5)

    # ok done, now let's try to access the hits as well

    eventhits = storehit[i]
    c_simhits = eventhits.get("C_caloHits")
    s_simhits = eventhits.get("S_caloHits")

    tot_s_hitenergy = 0
    tot_c_hitenergy = 0

    for hit in c_simhits:
        tot_c_hitenergy = tot_c_hitenergy + hit.getEnergy()
    for hit in s_simhits:
        tot_s_hitenergy = tot_s_hitenergy + hit.getEnergy()

    if (tot_c_energy != 0):
        h_c_ratio_simdigi.Fill(tot_c_hitenergy/tot_c_energy)
    if (tot_s_energy != 0):
        h_s_ratio_simdigi.Fill(tot_s_hitenergy/tot_s_energy)
    
    

ofile.Write()
ofile.Close()
