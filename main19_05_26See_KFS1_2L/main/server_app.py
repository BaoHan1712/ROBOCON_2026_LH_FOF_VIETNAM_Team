from flask import Flask, render_template
from flask_socketio import SocketIO, emit
from flask_cors import CORS
import subprocess

app = Flask(__name__, static_folder='static', static_url_path='/static')
CORS(app)
socketio = SocketIO(app, cors_allowed_origins="*")

global_state = {str(i): 'EMPTY' for i in range(1, 13)}
global_team = 'R'

def get_algo_matrix_internal():
    val_map = {'1': 1, '2': 2, 'Fake': 3, 'EMPTY': 0, None: 0}
    def get_v(cid): return val_map.get(global_state.get(str(cid)), 0)
    if global_team == 'R':
        return [[get_v(12), get_v(11), get_v(10)], [get_v(9), get_v(8), get_v(7)], [get_v(6), get_v(5), get_v(4)], [get_v(3), get_v(2), get_v(1)]]
    else:
        return [[get_v(10), get_v(11), get_v(12)], [get_v(7), get_v(8), get_v(9)], [get_v(4), get_v(5), get_v(6)], [get_v(1), get_v(2), get_v(3)]]

@app.route('/')
def home():
    return render_template('index.html')

@socketio.on('connect')
def handle_connect():
    emit('server_sync', {'state': global_state, 'team': global_team})

@socketio.on('client_click')
def handle_click(data):
    global global_state
    cell_id = str(data['id'])
    if cell_id != "0": 
        global_state[cell_id] = data['val']
    payload = {"team": global_team, "grid": get_algo_matrix_internal()}
    emit('server_sync', {'state': global_state, 'team': global_team}, broadcast=True)
    emit('sync_state', payload, broadcast=True)

@socketio.on('client_toggle_team')
def handle_toggle_team():
    global global_team, global_state
    mirror_map = {'12':'10','10':'12','9':'7','7':'9','6':'4','4':'6','3':'1','1':'3','11':'11','8':'8','5':'5','2':'2'}
    new_state = {mirror_map[old_id]: val for old_id, val in global_state.items()}
    global_state = new_state
    global_team = 'B' if global_team == 'R' else 'R'
    payload = {"team": global_team, "grid": get_algo_matrix_internal()}
    emit('server_sync', {'state': global_state, 'team': global_team}, broadcast=True)
    emit('sync_state', payload, broadcast=True)

@socketio.on('client_reset')
def handle_reset():
    global global_state
    global_state = {str(i): 'EMPTY' for i in range(1, 13)}
    payload = {"team": global_team, "grid": get_algo_matrix_internal()}
    emit('server_sync', {'state': global_state, 'team': global_team}, broadcast=True)
    emit('sync_state', payload, broadcast=True)
    
    # === THÊM DÒNG NÀY ĐỂ TRUYỀN THÁNH CHỈ XUỐNG ALGO ===
    emit('trigger_reset', {}, broadcast=True)
@socketio.on('client_set_target')
def handle_set_target(data):
    # Nhận data từ Web và phát thanh xuống Algo (chứa biến target: 2, 3, hoặc 4)
    emit('trigger_target', data, broadcast=True)
@socketio.on('client_trigger_algo')
def handle_trigger_algo():
    emit('trigger_algo', {}, broadcast=True)

@socketio.on('client_toggle_mode')
def handle_toggle_mode():
    emit('trigger_mode', {}, broadcast=True)

@socketio.on('client_toggle_strategy')
def handle_toggle_strategy():
    emit('trigger_strategy', {}, broadcast=True)

@socketio.on('client_replay_cache')
def handle_replay_cache():
    emit('trigger_replay', {}, broadcast=True)
@socketio.on('client_replay_cache')
def handle_replay_cache():
    emit('trigger_replay', {}, broadcast=True)

# =========================================================
# 🚀 TRẠM TRUNG CHUYỂN DÒ ĐƯỜNG (CÁI MÀY QUÊN MANG THEO)
# =========================================================
@socketio.on('client_find_path')
def handle_client_find_path(*args):
    print(">> [SERVER FLASK] Nhận lệnh DÒ ĐƯỜNG từ Web! Đang phát loa gọi App PC...")
    emit('trigger_find_path', {}, broadcast=True)

# =========================================================
# 🚀 TRẠM TRUNG CHUYỂN TRẢ KẾT QUẢ ĐƯỜNG ĐI (QUÊN NỮA NÀY SẾP!)
# =========================================================
@socketio.on('app_path_sync')
def handle_app_path_sync(data):
    # Hứng data đường đi từ App PC -> Bắn ngược lên Web để vẽ
    emit('server_path_sync', data, broadcast=True)

def get_local_ip():
    try:
        ip = subprocess.check_output("hostname -I", shell=True).decode().strip().split()[0]
        return ip
    except Exception:
        return "10.42.0.1"

if __name__ == '__main__':
    my_ip = get_local_ip()
    print("\n" + "★"*55)
    print("🚀 TRẠM CHỈ HUY (SERVER) ĐÃ CHẠY ĐỘC LẬP TỪ FILE MỚI!")
    print(f"📱 URL CHO ĐIỆN THOẠI: http://{my_ip}:5001")
    print("★"*55 + "\n")
    import logging
    logging.getLogger('werkzeug').setLevel(logging.ERROR)
    
    # SỬA LẠI DÒNG DƯỚI CÙNG NÀY: THÊM allow_unsafe_werkzeug=True
    socketio.run(
        app, 
        host='0.0.0.0', 
        port=5001, 
        debug=False, 
        use_reloader=False, 
        allow_unsafe_werkzeug=True
    )